// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <nether/nether.h>


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
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        program.LoadFromRawStrings(vertexShaderSource, fragmentShaderSource);

        float vertices[] = {
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        renderable.SetVerticesVec3(vertices, 12);
        renderable.SetIndicesVec3(indices, 6);
        renderable.Generate();

    }

    virtual void Cleanup() override
    {

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
