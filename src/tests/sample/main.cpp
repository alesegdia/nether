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
        GetRenderer().SetRendererClearColor({0.f, 1.f, 0.5f, 1.0f});
        GetRenderer().SetColorBufferBit(true);

        GetRenderer().BeginRender();
        GetRenderer().UseProgramShader(program);

        renderable.Render();

        GetRenderer().EndRender();
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
    nether::Renderable renderable;
    nether::ShaderProgram program;
    float vertices[32];

};

int main(int argc, char** argv) 
{
    SampleTest().Run();
    return 0;
}
