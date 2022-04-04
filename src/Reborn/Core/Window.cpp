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
		return { nullptr };
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

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
	ID3D11Device* pd3dDevice = nullptr;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11DeviceContext* pImmediateContext = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];


		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, //pAdapter
			driverType,
			nullptr, //Software
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&pSwapChain,
			&pd3dDevice,
			&featureLevel,
			&pImmediateContext
		);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,
				driverType,
				nullptr,
				createDeviceFlags,
				&featureLevels[1],
				numFeatureLevels - 1,
				D3D11_SDK_VERSION,
				&sd,
				&pSwapChain,
				&pd3dDevice,
				&featureLevel,
				&pImmediateContext
			);
		}

		if (SUCCEEDED(hr))
			break;
	}

	return { pImmediateContext, pd3dDevice, pSwapChain };
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