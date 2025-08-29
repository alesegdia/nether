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

            shader = nether::gl::createShader(GLenum(shaderType));
            nether::gl::shaderSource(shader, 1, &shaderStr, NULL);
            nether::gl::compileShader(shader);

            int success = 0;
            nether::gl::getShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                nether::gl::getShaderInfoLog(shader, 512, NULL, infoLog);
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
            nether::gl::deleteShader(shader);
        }

		const ShaderCompilationInfo& GetCompilationInfo()
		{
			return m_compilationInfo;
		}

    private:
        unsigned int shader = 0;
        ShaderCompilationInfo m_compilationInfo;

    };

}
