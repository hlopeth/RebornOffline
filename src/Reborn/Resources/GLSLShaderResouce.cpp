#include "Core.h"
#include "GLSLShaderResource.h"

#include <Core/Application.h>

Reborn::GLSLShaderResouce::GLSLShaderResouce(): 
	AbstractResource(0x78fd24ec)
{
}

Reborn::GLSLShaderResouce::GLSLShaderResouce(
	const std::string& _vertexSource, 
	const std::string& _fragmentSource
):
	AbstractResource(0x78fd24ec)
{
}

bool Reborn::GLSLShaderResouce::tryLoad(const std::string& path)
{
	std::ifstream inFile;
	const std::string vertexFilename = path + '/' + "vertex.glsl";
	inFile.open(vertexFilename);
	if (!inFile.is_open()) {
		LOG_ERROR << "GLSLShaderResouce::tryLoad feiled to open vertex shader " << vertexFilename;
		inFile.close();
		return false;
	}
	else {
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		program.vertexSource = buffer.str();
	}
	inFile.close();

	const std::string fragmentFilename = path + '/' + "fragment.glsl";
	inFile.open(fragmentFilename);
	if (!inFile.is_open()) {
		LOG_ERROR << "GLSLShaderResouce::tryLoad feiled to open fragment shader " << fragmentFilename;
		inFile.close();
		return false;
	}
	else {
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		program.fragmentSource = buffer.str();
	}
	inFile.close();

	loaded = true;

	Reborn::Renderer& renderer = Application::get()->renderer();
	renderer.create(program);
	return true;
}

bool Reborn::GLSLShaderResouce::unload()
{
	program.vertexSource = "";
 	program.fragmentSource = "";
	loaded = false;
	Application::get()->renderer().destroy(program);
	return true;
}

const Reborn::GLSLProgram& Reborn::GLSLShaderResouce::getProgram() const
{
	return program;
}
