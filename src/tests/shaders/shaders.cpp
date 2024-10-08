#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <nether/nether.h>

class RenderablePosColor
{
public:
    void Generate()
    {
        program.Load("media/shaders.vs", "media/shaders.fs");

        vao.Generate();
        vbo.Generate(nether::BufferBindingTarget::ArrayBuffer);

        vao.Bind();
         
        std::vector<float> vertices = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
        };

        vbo.Bind();
        vbo.UploadBufferData(vertices);

        vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 6 * sizeof(float), (void*)0 );
        vao.EnableVertexAttribArray(0);

        vao.AddVertexAttribPointer(1, 3, nether::GLType::Float, nether::GLBoolean::False, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
        vao.EnableVertexAttribArray(1);

        vbo.Unbind();
        vao.Unbind();
    }

    void Cleanup()
    {
        vao.Delete();
        vbo.Delete();
        program.Delete();
    }

    void Render()
    {
        program.Use();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    nether::VertexArrayObject vao;
    nether::BufferObject vbo;
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

        renderable.Render();
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
    RenderablePosColor renderable;

};

int main(int argc, char** argv) 
{
    SampleTest().Run();
    return 0;
}
