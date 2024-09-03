#pragma once

#include "nether/Shader.h"

namespace nether
{

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

}
