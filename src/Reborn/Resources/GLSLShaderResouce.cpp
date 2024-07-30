#include "Core.h"
#include "GLSLShaderResource.h"

#include <Core/Application.h>

Reborn::GLSLShaderResouce::GLSLShaderResouce(): 
	AbstractResource(0x78fd24ec)
{
}

Reborn::GLSLShaderResouce::GLSLShaderResouce(
	const Reborn::Handler _handle
):
	AbstractResource(0x78fd24ec),
	handle(_handle)
{
}

bool Reborn::GLSLShaderResouce::tryLoad(const std::string& path)
{
	std::ifstream inFile;
	const std::string vertexFilename = path + '/' + "vertex.glsl";
	inFile.open(vertexFilename);
	std::string vertexSource;
	std::string fragmentSource;
	if (!inFile.is_open()) {
		LOG_ERROR << "GLSLShaderResouce::tryLoad feiled to open vertex shader " << vertexFilename;
		inFile.close();
		return false;
	}
	else {
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		vertexSource = buffer.str();
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
		fragmentSource = buffer.str();
	}
	inFile.close();

	loaded = true;

	Reborn::Renderer& renderer = Application::get()->renderer();
	this->handle = renderer.createShaderProgram(vertexSource, fragmentSource);
	return true;
}

bool Reborn::GLSLShaderResouce::unload()
{
	loaded = false;
	Application::get()->renderer().deleteSharerProgram(handle	);
	return true;
}

const char* Reborn::GLSLShaderResouce::getTypeStr()
{
	return "GLSLShaderResouce";
}

const Reborn::Handler Reborn::GLSLShaderResouce::getProgram() const
{
	return handle;
}
