// gcc example/c/gl_sdl2.c build/src/gl.c -Ibuild/include `sdl2-config --libs --cflags` -ldl
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <nether/nether.h>

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



class SampleTest : public nether::TestApp
{
public:
    virtual void Step(float delta) override
    {
        GetRenderer().SetRendererClearColor({0.f, 1.f, 0.5f, 1.0f});
        GetRenderer().SetColorBufferBit(true);

        GetRenderer().BeginRender();

        renderable.Render();
    }

    virtual void Init() override
    {
        verticesTriangle = {
        { -0.5f, -0.5f,  0.0f },
        {  0.5f, -0.5f,  0.0f },
        {  0.0f,  0.5f,  0.0f },

        };

        verticesRect = {
            { 0.5f,  0.5f, 0.0f},  // top right
            { 0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f,  0.5f, 0.0f},  // top left 
            // second triangle
             {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f},  // bottom left
            {-0.5f,  0.5f, 0.0f}   // top left
        };

        renderable.SetVertices(verticesRect);
        renderable.Generate();


        program.Load("assets/vertexShader.vert", "assets/fragmentShader.frag");
    }

    virtual void Cleanup() override
    {

    }

private:
    std::vector<glm::fvec3> verticesTriangle;
    std::vector<glm::fvec3> verticesRect;
    nether::ShaderProgram program;
    float vertices[32];

};

int main(int argc, char** argv) 
{
    SampleTest().Run();
    return 0;
}
