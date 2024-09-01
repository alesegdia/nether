// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
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
        vbo.SetBufferBindingTarget(nether::BufferBindingTarget::ArrayBuffer);
        vbo.SetBufferUsage(nether::BufferUsage::StaticDraw);

        vao.Generate();
        vbo.Generate();

        vao.Bind();

        std::vector<float> vertices = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
        };

        vbo.Bind();
        vbo.UploadBufferData(vertices);

        vao.AddVertexAttribPointer(0, 3, nether::GLType::Float, nether::GLBoolean::False, 6 * sizeof(float), (void*)0);
        vao.EnableVertexAttribArray(0);

        vao.AddVertexAttribPointer(1, 3, nether::GLType::Float, nether::GLBoolean::False, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        vao.EnableVertexAttribArray(1);

        vbo.Unbind();
        vao.Unbind();
    }

    void Cleanup()
    {
        vao.Delete();
        vbo.Delete();
    }

    void Render()
    {
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    nether::VertexArrayObject vao;
    nether::BufferObject vbo;

};

class SampleTest : public nether::TestApp
{
public:
    virtual void Step(float delta) override
    {
        GetRenderer().SetRendererClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        GetRenderer().SetColorBufferBit(true);

        GetRenderer().BeginRender();
        GetRenderer().UseProgramShader(program);

        renderable.Render();

        GetRenderer().EndRender();
    }

    virtual void Init() override
    {
        program.Load("src/tests/shader/media/shader.vs", "src/tests/shader/media/shader.fs");
        renderable.Generate();

    }

    virtual void Cleanup() override
    {
        renderable.Cleanup();
        program.Delete();
    }

private:
    nether::Renderable renderable;
    nether::ShaderProgram program;

};

int main(int argc, char** argv) 
{
    SampleTest().Run();
    return 0;
}
