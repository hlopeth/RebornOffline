#pragma once
#include "Core.h"
#include "../Renderer.h"
#include <Math/MathUtils.h>
#include "backends/imgui_impl_dx11.h"
#include <backends/imgui_impl_sdl.h>


Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize) :
	_context(window.createRenderingContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
}

void Reborn::Renderer::beginFrame()
{
}


void Reborn::Renderer::endFrame(Reborn::ImGuiManager& imguiManager)
{
	_context.pDeviceContext->ClearRenderTargetView(_context.pRenderTargetView, ambientColor.d);

	imguiManager.render();

	_context.pSwapChain->Present(0, 0);
}

void Reborn::Renderer::drawVAO(const VertexArrayObject& vao, UIntValue offset)
{
}

void Reborn::Renderer::drawMesh(const Mesh& mesh)
{
}

const RenderingContext& Reborn::Renderer::getContext()
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

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const int& value)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const float& value)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Vector2& value)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Vector3& value)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Vector4& value)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Matrix2& value, bool transpose)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Matrix3& value, bool transpose)
{
}

void Reborn::Renderer::setUniform(const ShaderProgram& program, const CharValue* name, const Matrix4& value, bool transpose)
{
}

void Reborn::Renderer::create(ShaderProgram& program)
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

void Reborn::Renderer::create(TextureHandler& texture)
{
}

void Reborn::Renderer::upload(BufferObject& buf, EnumValue usage)
{
}

void Reborn::Renderer::upload(TextureHandler& texture, void* data, UIntValue mipLevel)
{
}

void Reborn::Renderer::upload(Renderbuffer& rbo)
{
}

void Reborn::Renderer::updateTextureParameters(TextureHandler& texture)
{
}

void Reborn::Renderer::setFramebufferTexture(Framebuffer& fbo, TextureHandler& texture, EnumValue attachment)
{
}

void Reborn::Renderer::setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, EnumValue attachment)
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

void Reborn::Renderer::bind(TextureHandler& texture)
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

void Reborn::Renderer::destroy(ShaderProgram& program)
{
}

void Reborn::Renderer::destroy(VertexArrayObject& vao)
{
}

void Reborn::Renderer::useProgram(const ShaderProgram& program)
{
}

Reborn::TextureHandler stubTexture;

const Reborn::TextureHandler& Reborn::Renderer::getSceneTexture()
{
	return stubTexture;
}

void Reborn::Renderer::setClearColor(const Vector3& color)
{
	this->ambientColor = color;
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
	ImGui_ImplSDL2_InitForD3D(window);
	ImGui_ImplDX11_Init(_context.pDevice, _context.pDeviceContext);
	return true;
}

void Reborn::Renderer::newImGuiFrame()
{
	ImGui_ImplDX11_NewFrame();
}

void Reborn::Renderer::drawImGui(ImDrawData* drawData)
{
	ImGui_ImplDX11_RenderDrawData(drawData);
}

void Reborn::Renderer::destroyImGui()
{
	ImGui_ImplDX11_Shutdown();
}