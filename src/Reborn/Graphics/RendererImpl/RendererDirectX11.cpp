#pragma once
#include "Core.h"
#include "../Renderer.h"
#include <Math/MathUtils.h>
#include "backends/imgui_impl_dx11.h"
#include <backends/imgui_impl_sdl.h>

//temp
ID3D11Texture2D* m_renderTargetTexture = nullptr;
ID3D11RenderTargetView* m_renderTargetView = nullptr;
ID3D11ShaderResourceView* m_shaderResourceView = nullptr;


ID3D11RenderTargetView* createRenderTargetView(RenderingContext& context) {
	ID3D11RenderTargetView* renderTargetView = nullptr;
	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	HRESULT hr = context.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
	{
		LOG_ERROR << "Failed to create swap chain. file: " << __FILE__ << " line: " << __LINE__;
		return nullptr;
	}

	hr = context.pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView);
	if (FAILED(hr))
	{
		LOG_ERROR << "Failed to create render target view. file: " << __FILE__ << " line: " << __LINE__;
		return nullptr;
	}
	pBackBuffer->Release();
	return renderTargetView;
}

void createRenderTexture(RenderingContext& context, Reborn::Window& window) 
{
	HRESULT hr;

	//https://www.rastertek.com/dx11tut22.html
	// Setup the render target texture description.
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = window.width();
	textureDesc.Height = window.height();
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //!!!!
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	hr = context.pDevice->CreateTexture2D(&textureDesc, nullptr, &m_renderTargetTexture);
	if (FAILED(hr))
	{
		LOG_ERROR << "Failed to create render target texture";
	}

	// Setup the description of the render target view.
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;
	hr = context.pDevice->CreateRenderTargetView(m_renderTargetTexture, &renderTargetViewDesc, &m_renderTargetView);
	if (FAILED(hr))
	{
		LOG_ERROR << "Failed to create render target view";
	}

	// Setup the description of the shader resource view.
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	hr = context.pDevice->CreateShaderResourceView(m_renderTargetTexture, &shaderResourceViewDesc, &m_shaderResourceView);
	if (FAILED(hr))
	{
		LOG_ERROR << "Failed to create render shader resource view";
	}
}

Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize) :
	_context(window.createRenderingContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
	renderTargetView = createRenderTargetView(_context);
	if (renderTargetView != nullptr)
	{
		_context.pDeviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
	}
	createRenderTexture(_context, _window);
}

void Reborn::Renderer::beginFrame()
{
}


void Reborn::Renderer::endFrame(Reborn::ImGuiManager& imguiManager)
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_window.width();
	vp.Height = (FLOAT)_window.height();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_context.pDeviceContext->RSSetViewports(1, &vp);

	_context.pDeviceContext->ClearRenderTargetView(renderTargetView, ambientColor.d);

	//imguiManager.render();

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