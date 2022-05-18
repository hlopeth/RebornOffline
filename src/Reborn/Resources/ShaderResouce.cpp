#include "Core.h"
#include "ShaderResource.h"

#include <Core/Application.h>

#if REBORN_OPENGL
#include <Graphics/Platform/OpenGL/GLRenderer.h>
#endif

Reborn::ShaderResouce::ShaderResouce(): 
	AbstractResource(0x78fd24ec),
	program(Reborn::APIType::NONE)
{
}

Reborn::ShaderResouce::ShaderResouce(
	const Reborn::ShaderProgram& _program
):
	AbstractResource(0x78fd24ec),
	program(_program)
{
}

#if REBORN_OPENGL
bool Reborn::ShaderResouce::tryLoad(const std::string& path)
{
	std::string vertexSource;
	std::string fragmentSource;

	std::ifstream inFile;
	const std::string vertexFilename = path + '/' + "vertex.glsl";
	inFile.open(vertexFilename);
	if (!inFile.is_open()) {
		LOG_ERROR << "ShaderResouce::tryLoad feiled to open vertex shader " << vertexFilename;
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
		LOG_ERROR << "ShaderResouce::tryLoad feiled to open fragment shader " << fragmentFilename;
		inFile.close();
		return false;
	}
	else {
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		fragmentSource = buffer.str();
	}
	inFile.close();

	Reborn::GLRenderer& glRenderer = static_cast<Reborn::GLRenderer&>(Reborn::Application::get()->renderer());
	program = glRenderer.create(vertexSource, fragmentSource);
	return true;
}

bool Reborn::ShaderResouce::unload()
{
	loaded = false;
	Reborn::GLRenderer& glRenderer = static_cast<Reborn::GLRenderer&>(Reborn::Application::get()->renderer());
	glRenderer.destroy(program);
	return true;
}
#endif

const char* Reborn::ShaderResouce::getTypeStr()
{
	return "ShaderResouce";
}

const Reborn::ShaderProgram& Reborn::ShaderResouce::getProgram() const
{
	return program;
}
