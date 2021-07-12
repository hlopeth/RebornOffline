#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

void GLAPIENTRY glMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
) {
	if (type == GL_DEBUG_TYPE_ERROR) {
		LOG_ERROR << "GL ERROR: type = " << type << ", severity = " << severity << ", message = " << message;
	}
	else {
		LOG_DEBUG << "GL CALLBACK: type = " << type << ", severity = " << severity << ", message = " << message;
	}
}

Reborn::Renderer::Renderer(Window& window):
	_context(window.createGLContext()),
	_window(window)
{
	initImGui(&window.getSDLWindow());

	auto glVersion = glGetString(GL_VERSION);
	auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	LOG_INFO << "usin OpenGL " << glVersion;

	glClearColor(1.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glMessageCallback, 0);
}

void Reborn::Renderer::draw()
{
	glViewport(0, 0, _window.width(), _window.height());
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(&(_window.getSDLWindow()));
}

const SDL_GLContext& Reborn::Renderer::getContext()
{
	return _context;
}

void Reborn::Renderer::generate(VBO& vbo)
{
	glGenBuffers(1, &(vbo.id));
}

void Reborn::Renderer::upload(VBO& vbo, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, vbo.size * sizeof(float), vbo.vertices.get(), usage);
}

void Reborn::Renderer::bind(VBO& vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
}

Reborn::Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(_context);
}

bool Reborn::Renderer::initImGui(SDL_Window* window) {
	if (!gladLoadGL()) {
		LOG_ERROR << "ImGuiSystem::init Failed to init glad";
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui_ImplSDL2_InitForOpenGL(window, _context);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	return true;
}