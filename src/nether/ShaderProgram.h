#pragma once

#include "nether/Shader.h"
#include "aether/core/logger.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace nether
{

    class ShaderProgram
    {
    public:

        void Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
        {
			m_shaderProgramCompilationInfo.fileLoad = true;

            nether::Shader vertexShader, fragmentShader;

            vertexShader.Load(vertexShaderFile, nether::ShaderType::VertexShader);
            m_vertexShaderCompilationInfo = vertexShader.GetCompilationInfo();

            fragmentShader.Load(fragmentShaderFile, nether::ShaderType::FragmentShader);
            m_fragmentShaderCompilationInfo = fragmentShader.GetCompilationInfo();

            Load(vertexShader, fragmentShader);
            vertexShader.Clean();
            fragmentShader.Clean();
        }

        void LoadFromRawStrings(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
        {
			m_shaderProgramCompilationInfo.fileLoad = false;

            nether::Shader vertexShader, fragmentShader;
            
            vertexShader.LoadCode(vertexShaderCode, nether::ShaderType::VertexShader);
            m_vertexShaderCompilationInfo = vertexShader.GetCompilationInfo();
            
            fragmentShader.LoadCode(fragmentShaderCode, nether::ShaderType::FragmentShader);
			m_fragmentShaderCompilationInfo =  fragmentShader.GetCompilationInfo();

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
                m_shaderProgramCompilationInfo.hasError = true;
				m_shaderProgramCompilationInfo.infoText = "Shader program linking failed: " + std::string(infoLog);
            }
            else
            {
				m_shaderProgramCompilationInfo.hasError = false;
				m_shaderProgramCompilationInfo.infoText = "Shader linking success!";
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

        void SetMat4Uniform(const std::string& name, const glm::mat4x4& mat)
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        void SetVec2Uniform(const std::string& name, const glm::fvec2& vec)
        {
            glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y);
        }


		ShaderCompilationInfo GetVertexShaderCompilationInfo() const
		{
			return m_vertexShaderCompilationInfo;
		}

        ShaderCompilationInfo GetFragmentShaderCompilationInfo() const
        {
            return m_fragmentShaderCompilationInfo;
        }

		ShaderCompilationInfo GetShaderProgramCompilationInfo() const
		{
			return m_shaderProgramCompilationInfo;
		}

    private:
        unsigned int shaderProgram;
        ShaderCompilationInfo m_fragmentShaderCompilationInfo;
        ShaderCompilationInfo m_vertexShaderCompilationInfo;
		ShaderCompilationInfo m_shaderProgramCompilationInfo;
    };

}
