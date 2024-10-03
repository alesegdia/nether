#pragma once

#include <string>

namespace nether
{
	class Texture;
	class ShaderProgram;

	void init();
	void exit();

	nether::Texture* newTexture(const std::string& path);
	nether::ShaderProgram* newShaderProgram(const std::string& vspath, const std::string& fspath);

}
