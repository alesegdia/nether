#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "nether/ShaderType.h"

namespace nether
{

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

}
