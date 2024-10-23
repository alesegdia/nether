#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <nether/nether.h>

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
        vao.Generate();
        vbo.Generate(nether::BufferBindingTarget::ArrayBuffer);
        ebo.Generate(nether::BufferBindingTarget::ElementArrayBuffer);

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
    nether::VertexArrayObject vao;
    nether::BufferObject vbo;
    nether::BufferObject ebo;
    std::vector<glm::fvec3> vertices;
    std::vector<glm::uvec3> indices;

};


class SampleTest : public nether::TestApp
{
public:
    virtual void Step(float delta) override
    {
        GetRenderer().SetRendererClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        GetRenderer().SetColorBufferBit(true);

        GetRenderer().BeginRender();
        program.Use();

        renderable.Render();
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

        renderable.SetVerticesVec3(vertices, 4);
        renderable.SetIndicesVec3(indices, 2);
        renderable.Generate();

    }

    virtual void Cleanup() override
    {
        renderable.Cleanup();
        program.Delete();
    }

private:
    Renderable renderable;
    nether::ShaderProgram program;

};

int main(int argc, char** argv) 
{
    SampleTest().Run();
    return 0;
}
