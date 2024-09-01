#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <rztl/rztl.h>

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

namespace nether
{

    struct Color
    {
        static const Color White;

        float r, g, b, a;
    };

    inline constexpr Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);


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

        template <typename T>
        void UploadBufferData(const std::vector<T>& items)
        {
            glBufferData(static_cast<GLenum>(bufferBindingTarget), sizeof(T) * items.size(), items.data(), GLenum(bufferUsage));
        }

        void Bind()
        {
            glBindBuffer(static_cast<GLenum>(bufferBindingTarget), vbo);
        }

        void Unbind()
        {
            glBindBuffer(static_cast<GLenum>(bufferBindingTarget), 0);
        }
        
        void Delete()
        {
            glDeleteBuffers(1, &vbo);
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

        void Delete()
        {
            glDeleteVertexArrays(2, &VAO);
        }

        void Unbind()
        {
            glBindVertexArray(0);
        }

    private:
        unsigned int VAO;

    };


    class Texture
    {
    public:
        Texture(const char* filePath)
        {
            int w, h, comp;
            m_data = stbi_load(filePath, &w, &h, &comp, 0);

            if (IsValid())
            {
                glGenTextures(1, &m_texture);
                glBindTexture(GL_TEXTURE_2D, m_texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(m_data);
            }
        }

        bool IsValid()
        {
            return m_data != nullptr;
        }

    private:
        unsigned char* m_data;
        unsigned int m_texture;

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

            LoadCode(shaderStr, shaderType);
        }

        void LoadCode(std::string code, ShaderType shaderType)
        {
            const char* shaderStr = code.c_str();

            shader = glCreateShader(GLenum(shaderType));
            glShaderSource(shader, 1, &shaderStr, NULL);
            glCompileShader(shader);

            int success = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "Shader with direct code compilation failed : " << infoLog << std::endl;
            }
            else
            {
                std::cout << "Shader with direct code compilation success!" << std::endl;
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

        void LoadFromRawStrings(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
        {
            nether::Shader vertexShader, fragmentShader;
            vertexShader.LoadCode(vertexShaderCode, nether::ShaderType::VertexShader);
            fragmentShader.LoadCode(fragmentShaderCode, nether::ShaderType::FragmentShader);
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

        void Delete()
        {
            glDeleteProgram(shaderProgram);
        }

        void SetBoolUniform(const std::string& name, bool value)
        {
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
        }

        void SetIntUniform(const std::string& name, int value)
        {
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
        }

        void SetFloatUniform(const std::string& name, float value)
        {
            glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
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

            // During init, enable debug output
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(MessageCallback, 0);

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

        void SetVerticesVec3(float* elements, int numElements)
        {
            vertices.clear();
            for (int i = 0; i < numElements; i++)
            {
                int offset = i * 3;
                vertices.push_back({ elements[offset + 0],
                                     elements[offset + 1],
                                     elements[offset + 2] });
            }
        }

        void SetIndicesVec3(unsigned int* elements, int numElements)
        {
            indices.clear();
            for (int i = 0; i < numElements; i++)
            {
                int offset = i * 3;
                indices.push_back({ elements[offset + 0],
                                    elements[offset + 1],
                                    elements[offset + 2] });
            }
        }

        void Generate()
        {
            vbo.SetBufferBindingTarget(nether::BufferBindingTarget::ArrayBuffer);
            vbo.SetBufferUsage(nether::BufferUsage::StaticDraw);

            ebo.SetBufferBindingTarget(nether::BufferBindingTarget::ElementArrayBuffer);
            ebo.SetBufferUsage(nether::BufferUsage::StaticDraw);

            vao.Generate();
            vbo.Generate();
            ebo.Generate();

            vao.Bind();

            vbo.Bind();
            vbo.UploadBufferData(vertices);

            ebo.Bind();
            ebo.UploadBufferData(indices);

            vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 3 * sizeof(float), (void*)0);
            vao.EnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void Cleanup()
        {
            vao.Delete();
            vbo.Delete();
            ebo.Delete();
        }

        void Render()
        {
            vao.Bind();
            glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
        }

    private:
        VertexArrayObject vao;
        BufferObject vbo;
        BufferObject ebo;
        std::vector<glm::fvec3> vertices;
        std::vector<glm::uvec3> indices;

    };

    class Material
    {
    public:

    };

    struct Rect
    {
        glm::ivec2 origin;
        glm::ivec2 size;

        bool operator==(const Rect& other)
        {
            return origin == other.origin &&
                size == other.size;
        }
    };

    struct Vertex
    {
        Vertex(const glm::fvec2& pPosition)
            : position(pPosition)
        {

        }

        Vertex(const glm::fvec2& pPosition, const Color& pColor)
            : position(pPosition),
            color(pColor)
        {

        }

        Vertex(const glm::fvec2& pPosition, const glm::fvec2& pTexCoords)
            : position(pPosition),
            texCoords(pTexCoords)
        {

        }

        Vertex(const glm::fvec2& pPosition, const glm::fvec2& pTexCoords, const Color& pColor)
            : position(pPosition),
            texCoords(pTexCoords),
            color(pColor)
        {

        }

        Vertex()
        {

        }

        glm::fvec2 position{ 0,0 };
        Color color{ Color::White };
        glm::fvec2 texCoords{ 0,0 };
    };

    class Sprite
    {
    public:
        Sprite(const std::shared_ptr<Texture>& texture, const Rect& rect)
        {
            SetTextureRect(rect);

        }

    private:
        void SetTextureRect(const Rect& rect)
        {
            if (rect != m_textureRect)
            {
                m_textureRect = rect;
                // updatePositions();
                // updateTexCoords();
            }
        }

        std::shared_ptr<Texture> m_texture;
        Vertex m_vertices[4];
        Rect m_textureRect;

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

        void SetWireframeMode()
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        void SetFillMode()
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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


    class TestApp
    {
    public:
        TestApp(int windowWidth = 800, int windowHeight = 600)
            : m_windowWidth(windowWidth)
            , m_windowHeight(windowHeight)
        {

        }

        virtual ~TestApp() {}
        
        virtual void Step(float delta) = 0;
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        void Run()
        {
            m_ctx.Init(800, 600);

            Init();

            int exit = 0;
            uint64_t ticks = SDL_GetTicks();

            while (!exit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_EVENT_QUIT:
                        exit = 1;
                        break;
                    case SDL_EVENT_KEY_UP:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            exit = 1;
                        }
                        if (event.key.keysym.sym == SDLK_w) {
                            GetRenderer().SetWireframeMode();
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                            GetRenderer().SetFillMode();
                        }
                        break;
                    default:
                        break;
                    }
                }

                auto currentTicks = SDL_GetTicks();
                float delta = currentTicks - ticks;
                Step(float(delta));
                ticks = currentTicks;

                m_ctx.EndFrame();
            }

            Cleanup();
            m_ctx.Cleanup();
        }

    protected:
        nether::SDLContext& GetCtx()
        {
            return m_ctx;
        }

        nether::Renderer& GetRenderer()
        {
            return m_renderer;
        }


    private:
        nether::SDLContext m_ctx;
        nether::Renderer m_renderer;
        int m_windowWidth = 0;
        int m_windowHeight = 0;


    };

}

