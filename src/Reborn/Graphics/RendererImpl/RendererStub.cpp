#pragma once
#include "Core.h"
#include "../Renderer.h"
#include <Math/MathUtils.h>

Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize) :
	_context(window.createGLContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
}

void Reborn::Renderer::beginFrame()
{
}

void Reborn::Renderer::drawImGui(ImDrawData* drawData)
{
}

void Reborn::Renderer::endFrame(Reborn::ImGuiManager& imguiManager)
{
}

void Reborn::Renderer::drawVAO(const VertexArrayObject& vao, GLuint offset)
{
}

void Reborn::Renderer::drawMesh(const Mesh& mesh)
{
}

const SDL_GLContext& Reborn::Renderer::getContext()
{
	return _context;
}

Reborn::Camera& Reborn::Renderer::getCamera()
{
	return _camera;
}

const Reborn::Camera& Reborn::Renderer::getCamera() const
{
	return _camera;
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const int& value)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const float& value)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector2& value)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector3& value)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector4& value)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix2& value, bool transpose)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix3& value, bool transpose)
{
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix4& value, bool transpose)
{
}

void Reborn::Renderer::create(GLSLProgram& program)
{
}

void Reborn::Renderer::create(BufferObject& buf)
{
}

void Reborn::Renderer::create(Framebuffer& fbo)
{
}

void Reborn::Renderer::create(Renderbuffer& rbo)
{
}

void Reborn::Renderer::create(VertexArrayObject& vao)
{
}

void Reborn::Renderer::create(GLTexture& texture)
{
}

void Reborn::Renderer::upload(BufferObject& buf, GLenum usage)
{
}

void Reborn::Renderer::upload(GLTexture& texture, void* data, GLuint mipLevel)
{
}

void Reborn::Renderer::upload(Renderbuffer& rbo)
{
}

void Reborn::Renderer::updateTextureParameters(GLTexture& texture)
{
}

void Reborn::Renderer::setFramebufferTexture(Framebuffer& fbo, GLTexture& texture, GLenum attachment)
{
}

void Reborn::Renderer::setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, GLenum attachment)
{
}

void Reborn::Renderer::bind(const BufferObject& buf)
{
}

void Reborn::Renderer::bind(const VertexArrayObject& vao)
{
}

void Reborn::Renderer::bind(const Framebuffer& fbo)
{
}

void Reborn::Renderer::bindMainFramebuffer()
{
}

void Reborn::Renderer::bind(GLTexture& texture)
{
}

void Reborn::Renderer::bind(Renderbuffer& rbo)
{
}

bool Reborn::Renderer::isFramebufferComplete(Framebuffer& fbo)
{
	return true;
}

void Reborn::Renderer::destroy(Framebuffer& fbo)
{
}

void Reborn::Renderer::destroy(GLSLProgram& program)
{
}

void Reborn::Renderer::destroy(VertexArrayObject& vao)
{
}

void Reborn::Renderer::useProgram(const GLSLProgram& program)
{
}

Reborn::GLTexture stubTexture;

const Reborn::GLTexture& Reborn::Renderer::getSceneTexture()
{
	return stubTexture;
}

void Reborn::Renderer::setClearColor(const Vector3& color)
{
}

Reborn::Vector2 stubFramebufferSize;

const Reborn::Vector2& Reborn::Renderer::getSceneFraimbufferSize()
{
	return stubFramebufferSize;
}

void Reborn::Renderer::setSceneFramebufferSize(const Vector2& newSize)
{
}

Reborn::Renderer::~Renderer()
{
}

bool Reborn::Renderer::create(FramebufferAttachment& fboAttachment)
{
	return false;
}

void Reborn::Renderer::attach(Framebuffer& fbo, FramebufferAttachment& fboAttachment) 
{
}

bool Reborn::Renderer::initImGui(SDL_Window* window) 
{
	return false;
}

void Reborn::Renderer::newImGuiFrame()
{
}

void Reborn::Renderer::destroyImGui()
{
}