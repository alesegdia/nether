// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <nether/nether.h>

#define SCR_W 800
#define SCR_H 600

class Renderable
{
public:
    void Generate()
    {

        // stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        tex1.LoadFromFile("media/container.jpg", nether::TextureFormat::RGB8);
        tex2.LoadFromFile("media/awesomeface.png", nether::TextureFormat::RGBA8);
        
        vao.Generate();
        vbo.Generate(nether::BufferBindingTarget::ArrayBuffer);

        vao.Bind();

        std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        vbo.Bind();
        vbo.UploadBufferData(vertices);

        vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 5 * sizeof(float), (void*)0 );
        vao.EnableVertexAttribArray(0);

        vao.AddVertexAttribPointer(1, 3, nether::GLType::Float, nether::GLBoolean::False, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        vao.EnableVertexAttribArray(1);

        vbo.Unbind();
        vao.Unbind();

        program.Load("media/transformations.vs", "media/transformations.fs");
        program.Use();

        program.SetIntUniform("texture1", 0);
        program.SetIntUniform("texture2", 1);
    }

    void Cleanup()
    {
        vao.Delete();
        vbo.Delete();
        program.Delete();
    }

    void Render(float delta)
    {
        time += delta;
        tex1.Bind(nether::TextureUnit::Texture0);
        tex2.Bind(nether::TextureUnit::Texture1);
        
        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 projection = glm::mat4(1.f);
        projection = glm::perspective(glm::radians(45.f), float(SCR_W) / float(SCR_H), 1.f, 100.f);
        view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

        program.SetMat4Uniform("projection", projection);
        program.SetMat4Uniform("view", view);

        vao.Bind();

        // world space positions of our cubes
        const std::vector<glm::vec3> cubePositions = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f;
            model = glm::rotate(model, glm::radians(angle) * i + time/1000, glm::vec3(1.f, 0.3f, 0.5f));
            program.SetMat4Uniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    }

private:
    float time = 0;
    nether::VertexArrayObject vao;
    nether::BufferObject vbo;

    nether::Texture tex1;
    nether::Texture tex2;

    nether::ShaderProgram program;

};

class SampleTest : public nether::TestApp
{
public:
    virtual void Step(float delta) override
    {
        GetRenderer().BeginRender();

        renderable.Render(delta);

    }

    virtual void Init() override
    {
        GetRenderer().SetDepthBufferBit(true);
        GetRenderer().SetColorBufferBit(true);
        GetRenderer().SetRendererClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

        renderable.Generate();

    }

    virtual void Cleanup() override
    {
        renderable.Cleanup();
    }

private:
    Renderable renderable;

};

int main(int argc, char** argv) 
{
    SampleTest().Run(SCR_W, SCR_H);
    return 0;
}
