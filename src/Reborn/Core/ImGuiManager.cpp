#include <Core.h>
#include "ImGuiManager.h"
#include <backends/imgui_impl_sdl.h>
#include <Graphics/Renderer.h>

void Reborn::ImGuiManager::init(Renderer& renderer, Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	initialized = renderer.initImGui(&window.getSDLWindow());
}

void Reborn::ImGuiManager::render(Renderer& renderer)
{
	if (initialized)
	{
		renderer.drawImGui(ImGui::GetDrawData());
	}
}

void Reborn::ImGuiManager::processEvent(SDL_Event& evt)
{
	if (initialized)
	{
		ImGui_ImplSDL2_ProcessEvent(&evt);
	}
}

void  Reborn::ImGuiManager::destroy(Renderer& renderer)
{
	if (initialized)
	{
		renderer.destroyImGui();
	}
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}