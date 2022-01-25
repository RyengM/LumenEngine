#include "Game/Asset/Public/ShaderLabCompiler.h"
#include <fstream>
#include <filesystem>

using namespace Lumen::Game;

ShaderLabCompiler& ShaderLabCompiler::GetInstance()
{
	static ShaderLabCompiler instance;
	return instance;
}

ShaderLab ShaderLabCompiler::Compile(std::string_view sourceFile)
{
	ShaderLab shaderLab;

	std::ifstream ifile(sourceFile.data());
	if (!ifile.is_open())
		return shaderLab;
	std::ostringstream buf;
	buf << ifile.rdbuf();

	return mShaderLabGenerator.Compile(buf.str());
}