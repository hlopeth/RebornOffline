#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>


bool imgui_initialized = false;
bool show_demo_window = true;

void initImGui(SDL_Window* window, SDL_GLContext context) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(window, context);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void imGuiFrame() {
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Render();
}

Reborn::Renderer::Renderer(SDL_GLContext context):
	_context(context)
{
	if (!gladLoadGL()) {
		LOG_ERROR << "Failed to init glad";
	}
	glClearColor(1.0, 0.0, 0.0, 1.0);

}

void Reborn::Renderer::draw(Window& window)
{
	if (!imgui_initialized) {
		initImGui(&window.getSDLWindow(), _context);
		imgui_initialized = true;
	}

	imGuiFrame();

	glViewport(0, 0, window.width(), window.height());
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(&(window.getSDLWindow()));
}

const SDL_GLContext& Reborn::Renderer::getContext()
{
	return _context;
}

Reborn::Renderer::~Renderer()
{
	if (imgui_initialized) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
	SDL_GL_DeleteContext(_context);
}
