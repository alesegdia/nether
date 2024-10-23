// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stb_image.h>

#include <nether/nether.h>

class Renderable
{
public:
    void Generate()
    {
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        tex1.LoadFromFile("media/container.jpg", nether::TextureFormat::RGB8);
        tex2.LoadFromFile("media/awesomeface.png", nether::TextureFormat::RGBA8);
        
        vao.Generate();
        vbo.Generate(nether::BufferBindingTarget::ArrayBuffer);
        ebo.Generate(nether::BufferBindingTarget::ElementArrayBuffer);

        vao.Bind();

        std::vector<float> vertices = {
            // positions          // texture coords

            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, // top left 
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        };
        std::vector<unsigned int> indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        vbo.Bind();
        vbo.UploadBufferData(vertices);

        ebo.Bind();
        ebo.UploadBufferData(indices);

        vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 5 * sizeof(float), (void*)0 );
        vao.EnableVertexAttribArray(0);

        vao.AddVertexAttribPointer(1, 3, nether::GLType::Float, nether::GLBoolean::False, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        vao.EnableVertexAttribArray(1);

        vbo.Unbind();
        vao.Unbind();
        ebo.Unbind();

        program.Load("media/coordinate-systems.vs", "media/coordinate-systems.fs");
        program.Use();

        program.SetIntUniform("texture1", 0);
        program.SetIntUniform("texture2", 1);
    }

    void Cleanup()
    {
        vao.Delete();
        ebo.Delete();
        vbo.Delete();
        program.Delete();

    }

    void Render(float delta)
    {
        time += delta;
        tex1.Bind(nether::TextureUnit::Texture0);
        tex2.Bind(nether::TextureUnit::Texture1);
        
        glm::mat4 transform = glm::mat4(1.f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        float angle = time / 1000.f;
        transform = glm::rotate(transform, angle, glm::vec3(0.f, 0.f, 1.f));

        program.Use();
        program.SetMat4Uniform("transform", transform);

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:
    float time = 0;
    nether::VertexArrayObject vao;
    nether::BufferObject vbo;
    nether::BufferObject ebo;

    nether::Texture tex1;
    nether::Texture tex2;

    nether::ShaderProgram program;

};

class SampleTest : public nether::TestApp
{
public:
    virtual void Step(float delta) override
    {
        GetRenderer().SetRendererClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        GetRenderer().SetColorBufferBit(true);

        GetRenderer().BeginRender();

        renderable.Render(delta);

    }

    virtual void Init() override
    {
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
    SampleTest().Run();
    return 0;
}
