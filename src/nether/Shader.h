#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "nether/ShaderType.h"

namespace nether
{

    struct ShaderCompilationInfo
    {
        bool hasError = false;
        std::string infoText;
        bool fileLoad = false;
        std::string filePath;
    };

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
            m_compilationInfo.fileLoad = true;
            m_compilationInfo.filePath = filePath;
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
                m_compilationInfo.hasError = true;
                // TODO: finish error handling
				if (m_compilationInfo.fileLoad)
                    m_compilationInfo.infoText = "Shader with path " + m_compilationInfo.filePath + " failed : " + std::string(infoLog);
				else
                    m_compilationInfo.infoText = "Shader with direct code compilation failed : " + std::string(infoLog);
            }
            else
            {
				if (m_compilationInfo.fileLoad)
                    m_compilationInfo.infoText = "Shader with path " + m_compilationInfo.filePath + " success!";
				else
                    m_compilationInfo.infoText = "Shader with direct code compilation success!";
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

		const ShaderCompilationInfo& GetCompilationInfo()
		{
			return m_compilationInfo;
		}

    private:
        unsigned int shader;
        ShaderCompilationInfo m_compilationInfo;

    };

}
