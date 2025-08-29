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
            shaderProgram = nether::gl::createProgram();
            nether::gl::attachShader(shaderProgram, vertexShader.GetShaderObject());
            nether::gl::attachShader(shaderProgram, fragmentShader.GetShaderObject());
            nether::gl::linkProgram(shaderProgram);

            int success = 0;
            nether::gl::getProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                nether::gl::getProgramInfoLog(shaderProgram, 512, NULL, infoLog);
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
            nether::gl::useProgram(shaderProgram);
        }

        void Unbind()
        {
            nether::gl::useProgram(0);
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
            nether::gl::deleteProgram(shaderProgram);
        }

        void SetBoolUniform(const std::string& name, bool value)
        {
            nether::gl::uniform1i(nether::gl::getUniformLocation(shaderProgram, name.c_str()), (int)value);
        }

        void SetIntUniform(const std::string& name, int value)
        {
            nether::gl::uniform1i(nether::gl::getUniformLocation(shaderProgram, name.c_str()), value);
        }

        void SetFloatUniform(const std::string& name, float value)
        {
            nether::gl::uniform1f(nether::gl::getUniformLocation(shaderProgram, name.c_str()), value);
        }

        void SetMat4Uniform(const std::string& name, const glm::mat4x4& mat)
        {
            nether::gl::uniformMatrix4fv(nether::gl::getUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        void SetVec2Uniform(const std::string& name, const glm::fvec2& vec)
        {
            nether::gl::uniform2f(nether::gl::getUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y);
        }

        void SetVec3Uniform(const std::string& name, const glm::fvec3& vec)
        {
            nether::gl::uniform3f(nether::gl::getUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z);
        }

        void SetVec4Uniform(const std::string& name, const glm::fvec4& vec)
        {
            nether::gl::uniform4f(nether::gl::getUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z, vec.a);
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
