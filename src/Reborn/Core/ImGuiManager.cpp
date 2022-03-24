#include <Core.h>
#include "ImGuiManager.h"
#include <backends/imgui_impl_sdl.h>
#include <Graphics/Renderer.h>

void Reborn::ImGuiManager::init(Renderer* renderer, Window* window)
{
	if (renderer == nullptr || window == nullptr) {
		_initialized = false;
		return;
	}
	_renderer = renderer;
	_window = window;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	_initialized = renderer->initImGui(&window->getSDLWindow());
}

bool Reborn::ImGuiManager::newFrame()
{
	if (_initialized) {
		ImGui_ImplSDL2_NewFrame(&_window->getSDLWindow());
		_renderer->newImGuiFrame();
		ImGui::NewFrame();
	}
	return _initialized;
}

void Reborn::ImGuiManager::render()
{
	if (_initialized)
	{
		_renderer->drawImGui(ImGui::GetDrawData());
	}
}

void Reborn::ImGuiManager::processEvent(SDL_Event& evt)
{
	if (_initialized)
	{
		ImGui_ImplSDL2_ProcessEvent(&evt);
	}
}

void  Reborn::ImGuiManager::destroy()
{
	if (_initialized)
	{
		_renderer->destroyImGui();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
}

bool Reborn::ImGuiManager::initialized()
{
	return _initialized;
}
