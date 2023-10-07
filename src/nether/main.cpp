// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace nether
{

    struct Color
    {
        float r, g, b, a;
    };
    
    enum class BufferBindingTarget : GLenum
    {
        ArrayBuffer = GL_ARRAY_BUFFER,
        ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
    };

    enum class BufferUsage : GLenum
    {
        StaticDraw = GL_STATIC_DRAW,    // the data is set only once and used by the GPU at most a few times
        StreamDraw = GL_STREAM_DRAW,    // the data is set only once and used many times
        DynamicDraw = GL_DYNAMIC_DRAW   // the data is changed a lot and used many times
    };

    class BufferObject
    {
    public:
        void Generate()
        {
            glGenBuffers(1, &vbo);
        }

        void SetBufferUsage(BufferUsage pBufferUsage)
        {
            bufferUsage = pBufferUsage;
        }

        void SetBufferBindingTarget(BufferBindingTarget pBufferBindingTarget)
        {
            bufferBindingTarget = pBufferBindingTarget;
        }

		void UploadBufferData(std::vector<glm::fvec3> vec3s)
		{
            UploadBufferData(&vec3s[0].x, vec3s.size() * 3);
		}

		void UploadBufferData(float* items, int num)
		{
			glBufferData(static_cast<GLenum>(bufferBindingTarget), num, items, GLenum(bufferUsage));
		}

        void Bind()
        {
			glBindBuffer(static_cast<GLenum>(bufferBindingTarget), vbo);
        }

        void Unbind()
        {
			glBindBuffer(static_cast<GLenum>(bufferBindingTarget), 0);
        }

    private:
		BufferUsage bufferUsage = BufferUsage::StaticDraw;
        BufferBindingTarget bufferBindingTarget = BufferBindingTarget::ArrayBuffer;
        unsigned int vbo;

    };

    enum class GLType : GLuint
    {
        Float = GL_FLOAT,
        Int = GL_INT,
        Bool = GL_BOOL
    };

    enum class GLBoolean : GLboolean
    {
        True = GL_TRUE,
        False = GL_FALSE
    };

	class VertexArrayObject
	{
	public:
        void Generate()
        {
			glGenVertexArrays(1, &VAO);
        }

        void AddVertexAttribPointer(unsigned int index, int size, GLType type, GLBoolean normalized, GLsizei stride, GLvoid* pointer)
        {
            glVertexAttribPointer(index, size, GLenum(type), GLboolean(normalized), stride, pointer);
        }

        void Bind()
        {
            glBindVertexArray(VAO);
        }

        void EnableVertexAttribArray(unsigned int index)
        {
            glEnableVertexAttribArray(index);
        }

    private:
        unsigned int VAO;

	};



    enum ShaderType : GLenum
    {
        VertexShader = GL_VERTEX_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER
    };

    class Shader
    {
    public:
        void Load(std::string filePath, ShaderType shaderType)
        {
			std::ifstream t(filePath);
			std::stringstream buffer;
			buffer << t.rdbuf();
            auto contents = buffer.str();
            const char* shaderStr = contents.c_str();
        
            shader = glCreateShader(GLenum(shaderType));
            glShaderSource(shader, 1, &shaderStr, NULL);
            glCompileShader(shader);

            int success = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
			{
				char infoLog[512];
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cout << "Shader " << filePath << " compilation failed : " << infoLog << std::endl;
            }
            else
            {
				std::cout << "Shader " << filePath << " compilation success!" << std::endl;
            }
        }

        unsigned int GetShaderObject()
        {
            return shader;
        }

		void Clean()
		{
            glDeleteShader(shader);
		}

    private:
        unsigned int shader;

    };

    class ShaderProgram
    {
    public:

        void Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
        {
			nether::Shader vertexShader, fragmentShader;
			vertexShader.Load(vertexShaderFile, nether::ShaderType::VertexShader);
			fragmentShader.Load(fragmentShaderFile, nether::ShaderType::FragmentShader);
			Load(vertexShader, fragmentShader);
			vertexShader.Clean();
			fragmentShader.Clean();
        }

        void Load(Shader vertexShader, Shader fragmentShader)
        {
            shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader.GetShaderObject());
			glAttachShader(shaderProgram, fragmentShader.GetShaderObject());
            glLinkProgram(shaderProgram);

			int success = 0;
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success) {
				char infoLog[512];
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "=================================================" << std::endl
                    << "Shader program linking failed: " << std::endl
                    << infoLog << std::endl
                    << "=================================================" << std::endl;
			}
            else
            {
				std::cout << "Shader linking success!" << std::endl;
            }
        }

		void Use()
		{
			glUseProgram(shaderProgram);
		}

		void Unbind()
		{
			glUseProgram(0);
		}

		bool operator==(const ShaderProgram& other)
		{
			return shaderProgram == other.shaderProgram;
		}

		bool operator!=(const ShaderProgram& other)
		{
			return shaderProgram != other.shaderProgram;
		}

    private:
        unsigned int shaderProgram;

    };



    class SDLContext
    {
    public:
        void Init(int width, int height)
        {
            // code without checking for errors
            SDL_Init(SDL_INIT_VIDEO);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            window = SDL_CreateWindow(
                "[glad] GL with SDL",
                width, height,
                SDL_WINDOW_OPENGL
            );

            context = SDL_GL_CreateContext(window);

            int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
            printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

        }

        void EndFrame()
        {
            SDL_GL_SwapWindow(window);
        }

        void Cleanup()
        {
            SDL_GL_DeleteContext(context);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

    private:
        SDL_Window* window;
        SDL_GLContext context;

    };

    class Scene
    {
    public:

    };

    class SceneNode
    {
    public:


    private:
        glm::fvec2 position;

    };


	class Renderable
	{
	public:
        void SetVertices(std::vector<glm::fvec3> pvertices)
        {
            vertices = pvertices;
        }

        void Generate()
        {
			vbo.SetBufferBindingTarget(nether::BufferBindingTarget::ArrayBuffer);
			vbo.SetBufferUsage(nether::BufferUsage::StaticDraw);

			vbo.Generate();
			vao.Generate();

			vao.Bind();
			vbo.Bind();

			vbo.UploadBufferData(&vertices[0].x, sizeof(float) * vertices.size() * 3);
			vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 3 * sizeof(float), (void*)0);
			vao.EnableVertexAttribArray(0);
        }

        void Render()
        {
			vao.Bind();
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        }

	private:
		VertexArrayObject vao;
		BufferObject vbo;
        std::vector<glm::fvec3> vertices;

	};

    class Material
    {
    public:

    };


    class Renderer
    {
    public:

        void SetRendererClearColor(Color color)
        {
            clearColor = color;
        }

        void BeginRender()
        {
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void EndRender()
        {

        }

        void SetColorBufferBit(bool set)
        {
            colorBufferBit = set;
            SetClearBits();
        }

        void SetDepthBufferBit(bool set)
        {
            depthBufferBit = set;
            SetClearBits();
        }

        /*
        void SetAccumBufferBit(bool set)
        {
            accumBufferBit = set;
        }
        */

        void SetStencilBufferBit(bool set)
        {
            stencilBufferBit = set;
            SetClearBits();
        }

        void UseProgramShader(ShaderProgram program)
        {
            if (!IsShaderProgramInUse || program != currentShaderProgramInUse)
            {
                IsShaderProgramInUse = true;
                currentShaderProgramInUse = program;
                currentShaderProgramInUse.Use();
            }
        }

        void UnbindProgram()
        {
            IsShaderProgramInUse = false;
            currentShaderProgramInUse.Unbind();
        }


    private:

        void SetClearBits()
        {
            SetBit(colorBufferBit, GL_COLOR_BUFFER_BIT);
            SetBit(depthBufferBit, GL_DEPTH_BUFFER_BIT);
            // SetBit(accumBufferBit, GL_ACCUM_BUFFER_BIT);
            SetBit(stencilBufferBit, GL_STENCIL_BUFFER_BIT);
        }

        void SetBit(bool set, GLbitfield bitField)
        {
            if (set)
            {
                clearBitField |= bitField;
            }
        }

        Color clearColor;
        GLbitfield clearBitField;
        bool colorBufferBit = false;
        bool depthBufferBit = false;
        // bool accumBufferBit = false;
        bool stencilBufferBit = false;

        bool IsShaderProgramInUse = false;
        ShaderProgram currentShaderProgramInUse;

    };


}


const GLuint WIDTH = 800, HEIGHT = 600;

int main(int argc, char** argv) {

	nether::SDLContext ctx;
	nether::Renderer renderer;
    ctx.Init(800, 600);

	std::vector<glm::fvec3> verticesTriangle{
	{ -0.5f, -0.5f,  0.0f },
	{  0.5f, -0.5f,  0.0f },
	{  0.0f,  0.5f,  0.0f },

	};

	std::vector<glm::fvec3> verticesRect{
    { 0.5f,  0.5f, 0.0f},  // top right
    { 0.5f, -0.5f, 0.0f},  // bottom right
    {-0.5f,  0.5f, 0.0f},  // top left 
    // second triangle
     {0.5f, -0.5f, 0.0f},  // bottom right
    {-0.5f, -0.5f, 0.0f},  // bottom left
    {-0.5f,  0.5f, 0.0f}   // top left
	};

	nether::Renderable renderable;
	renderable.SetVertices(verticesRect);
    renderable.Generate();

    nether::ShaderProgram program;
    program.Load("assets/vertexShader.vert", "assets/fragmentShader.frag");

    int exit = 0;
    while(!exit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT:
                    exit = 1;
                    break;
                case SDL_EVENT_KEY_UP:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        exit = 1;
                    }
                    break;
                default:
                    break;
            }
        }

        renderer.SetRendererClearColor({ 0.f, 1.f, 0.5f, 1.0f });
        renderer.SetColorBufferBit(true);

        renderer.BeginRender();
        renderer.UseProgramShader(program);

        renderable.Render();

        renderer.EndRender();

        ctx.EndFrame();
    }

    ctx.Cleanup();

    return 0;
}
