#include "Core.h"
#include "Window.h"

#include <imgui.h>

#ifdef REBORN_DIRECTX11
#include "SDL_syswm.h"
#endif

Reborn::Window::Window(SDL_Window* sdlWindow)
{
	_sdlWindow = sdlWindow;
}

#ifdef REBORN_OPENGL

RenderingContext Reborn::Window::createRenderingContext()
{
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GLContext context = SDL_GL_CreateContext(_sdlWindow);
	if (!context) {
		LOG_ERROR << "Failed to create context. \n" << SDL_GetError();
		context = nullptr;
	}
	return context;
}

#else
#ifdef REBORN_DIRECTX11
RenderingContext Reborn::Window::createRenderingContext()
{
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(_sdlWindow, &info);

	if (info.subsystem != SDL_SYSWM_WINDOWS) {
		LOG_ERROR << "expected SDL_SYSWM_WINDOWS in func " << __func__ << ", in file " << __FILE__ << " line " << __LINE__;
		return nullptr;
	}

	HWND hwnd = info.info.win.window;

	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
	ID3D11Device* pd3dDevice = nullptr;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11DeviceContext* pImmediateContext = nullptr;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];
		HRESULT hr = D3D11CreateDevice(
			nullptr, 
			driverType, 
			nullptr, 
			createDeviceFlags, 
			featureLevels, 
			numFeatureLevels,
			D3D11_SDK_VERSION, 
			&pd3dDevice, 
			&featureLevel, 
			&pImmediateContext
		);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(
				nullptr, 
				driverType, 
				nullptr, 
				createDeviceFlags, 
				&featureLevels[1], 
				numFeatureLevels - 1,
				D3D11_SDK_VERSION, 
				&pd3dDevice, 
				&featureLevel,
				&pImmediateContext
			);
		}

		if (SUCCEEDED(hr))
			break;
	}

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		HRESULT hr = pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}

	ID3D11Device1* pd3dDevice1 = nullptr;
	ID3D11DeviceContext1* pImmediateContext1 = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	IDXGISwapChain1* pSwapChain1 = nullptr;

	// Create swap chain
	IDXGIFactory2* dxgiFactory2 = nullptr;
	HRESULT hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		hr = pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&pd3dDevice1));
		if (SUCCEEDED(hr))
		{
			(void)pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&pImmediateContext1));
		}

		DXGI_SWAP_CHAIN_DESC1 sd = {};
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(pd3dDevice, hwnd, &sd, nullptr, nullptr, &pSwapChain1);
		if (SUCCEEDED(hr))
		{
			hr = pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&pSwapChain));
		}

		dxgiFactory2->Release();
}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(pd3dDevice, &sd, &pSwapChain);
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	if (FAILED(hr))
		return nullptr;

	ID3D11RenderTargetView* pRenderTargetView = nullptr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return nullptr;

	hr = pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return nullptr;

	pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pImmediateContext->RSSetViewports(1, &vp);

	return pImmediateContext;
}
#else 
RenderingContext Reborn::Window::createRenderingContext()
{
	return 0;
}
#endif // REBORN_DIRECTX11
#endif // REBORN_OPENGL



SDL_Window& Reborn::Window::getSDLWindow()
{
	return *_sdlWindow;
}

const int Reborn::Window::width() const
{
	int width;
	int height;
	SDL_GetWindowSize(_sdlWindow, &width, &height);
	return width;
}

const int Reborn::Window::height() const
{
	int width;
	int height;
	SDL_GetWindowSize(_sdlWindow, &width, &height);
	return height;
}

void Reborn::Window::Update()
{
	//SDL_UpdateWindowSurface(_sdlWindow);
}

Reborn::Window::~Window()
{
	SDL_DestroyWindow(_sdlWindow);
}

Reborn::Window* Reborn::Window::CreateSDLWindow(WindowConfiguration config)
{

	Uint16 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if(config.resizable)
		flags |= SDL_WINDOW_RESIZABLE;
	if(config.fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	SDL_Window* sdlWindow = SDL_CreateWindow(config.title, config.x, config.y, config.width, config.height, flags);
	if (sdlWindow == nullptr) {
		LOG_ERROR << "Failed to create SDL window. \n" << SDL_GetError();
	}
	return new Window(sdlWindow);
}