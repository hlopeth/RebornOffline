#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

Reborn::VertexArrayObject* test_vao;
Reborn::GLSLProgram* test_program;

GLuint compileShader(const std::string& source, GLenum type);

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

	LOG_INFO << "using OpenGL " << glVersion;

	glClearColor(0.2, 0.2, 0.2, 1.0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glMessageCallback, 0);


	std::string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	std::string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	test_program = new GLSLProgram(vertexShaderSource, fragmentShaderSource);

	create(*test_program);

	std::shared_ptr<float[]> vertices(new float[] {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
		});
	VertexBufferObject vbo(vertices, 9);
	std::vector<VertexAttribute> layout;
	layout.emplace_back(3, 3*sizeof(float), GL_FALSE, GL_FLOAT);
	test_vao = new VertexArrayObject(vbo, layout);

	create(*test_vao);
}

void Reborn::Renderer::beginFrame()
{
	glViewport(0, 0, _window.width(), _window.height());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Reborn::Renderer::endFrame()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(&(_window.getSDLWindow()));
}

void Reborn::Renderer::drawVAO(VertexArrayObject& vao, GLuint vertices, GLuint offset)
{
	bind(vao);
	glDrawArrays(GL_TRIANGLES, offset, vertices);
}

const SDL_GLContext& Reborn::Renderer::getContext()
{
	return _context;
}

void Reborn::Renderer::create(GLSLProgram& program)
{
	GLuint vertexShader = compileShader(program.vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(program.fragmentSource, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		LOG_ERROR << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	program.id = shaderProgram;
}

void Reborn::Renderer::create(VertexBufferObject& vbo)
{
	glGenBuffers(1, &(vbo.id));
}

void Reborn::Renderer::create(VertexArrayObject& vao)
{
	glGenVertexArrays(1, &(vao.id));
	bind(vao);

	create(vao.vbo);
	bind(vao.vbo);
	upload(vao.vbo);

	//void* offsetAcc = 0;
	for (int i = 0; i < vao.layout.size(); i++) {
		auto& attrib = vao.layout[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrib.size, attrib.type, attrib.normalized ,attrib.stride, (void*)0);
		//offsetAcc += attrib.stride;
	}
}

void Reborn::Renderer::upload(VertexBufferObject& vbo, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, vbo.size * sizeof(float), vbo.vertices.get(), usage);
}

void Reborn::Renderer::createLayout(VertexArrayObject vao)
{

}

void Reborn::Renderer::bind(VertexBufferObject& vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
}

void Reborn::Renderer::bind(VertexArrayObject& vao)
{
	glBindVertexArray(vao.id);
}

void Reborn::Renderer::useProgram(const GLSLProgram& program)
{
	glUseProgram(program.id);
}

void Reborn::Renderer::setClearColor(const Vector3& color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
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

GLuint compileShader(const std::string& source, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const GLchar* c_source = source.c_str();
	glShaderSource(shader, 1, &c_source, NULL);
	glCompileShader(shader);

	GLint success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		LOG_ERROR << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog;
	}
	return shader;
}