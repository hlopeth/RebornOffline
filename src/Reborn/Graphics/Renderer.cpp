#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

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

Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize):
	_context(window.createGLContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize)
{
	initImGui(&window.getSDLWindow());

	auto glVersion = glGetString(GL_VERSION);
	auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	LOG_INFO << "using OpenGL " << glVersion;

	glClearColor(0.2, 0.2, 0.2, 1.0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glMessageCallback, 0);

	create(sceneFraimbuffer);
	bind(sceneFraimbuffer);

	colorAttachmentTexture.width = sceneFraimbufferSize.x;
	colorAttachmentTexture.height = sceneFraimbufferSize.y;
	colorAttachmentTexture.textureType = GL_TEXTURE_2D;
	colorAttachmentTexture.internalFromat = GL_RGB;
	colorAttachmentTexture.texelFormat = GL_RGB;
	colorAttachmentTexture.texelType = GL_UNSIGNED_BYTE;
	colorAttachmentTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	colorAttachmentTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	create(colorAttachmentTexture);
	bind(colorAttachmentTexture);
	upload(colorAttachmentTexture, NULL);
	updateTextureParameters(colorAttachmentTexture);

	depthStencilRenderbuffer.width = sceneFraimbufferSize.x;
	depthStencilRenderbuffer.height = sceneFraimbufferSize.y;
	depthStencilRenderbuffer.internalFormat = GL_DEPTH24_STENCIL8;
	create(depthStencilRenderbuffer);
	bind(depthStencilRenderbuffer);
	upload(depthStencilRenderbuffer);

	setFramebufferTexture(sceneFraimbuffer, colorAttachmentTexture, GL_COLOR_ATTACHMENT0);
	setFramebufferRenderbuffer(sceneFraimbuffer, depthStencilRenderbuffer, GL_DEPTH_STENCIL_ATTACHMENT);

	if (!isFramebufferComplete(sceneFraimbuffer)) {
		LOG_ERROR << "main framebuffer is not complete";
	}

	bindMainFramebuffer();
}

void Reborn::Renderer::beginFrame()
{
	bind(sceneFraimbuffer);
	glViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool p_open = true;

void Reborn::Renderer::endFrame()
{
	bindMainFramebuffer();
	glViewport(0, 0, _window.width(), _window.height());
	glClear(GL_COLOR_BUFFER_BIT);

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

void Reborn::Renderer::create(Framebuffer& fbo)
{
	glGenFramebuffers(1, &(fbo.id));
}

void Reborn::Renderer::create(Renderbuffer& rbo)
{
	glGenRenderbuffers(1, &(rbo.id));
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

void Reborn::Renderer::create(GLTexture& texture)
{
	glGenTextures(1, &(texture.id));
}

void Reborn::Renderer::upload(VertexBufferObject& vbo, GLenum usage)
{
	bind(vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo.size * sizeof(float), vbo.vertices.get(), usage);
}

void Reborn::Renderer::upload(GLTexture& texture, void* data, GLuint mipLevel)
{
	bind(texture);
	switch (texture.textureType)
	{
	case GL_TEXTURE_2D:
		glTexImage2D(GL_TEXTURE_2D, mipLevel, texture.internalFromat, texture.width, texture.height, 0, texture.texelFormat, texture.texelType, data);
		break;
	default:
		LOG_ERROR << "Renderer::upload unsuplorted texture type = " << texture.textureType;
		break;
	}
}

void Reborn::Renderer::upload(Renderbuffer& rbo)
{
	bind(rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, rbo.internalFormat, rbo.width, rbo.height);
}

void Reborn::Renderer::createLayout(VertexArrayObject vao)
{

}

void Reborn::Renderer::updateTextureParameters(GLTexture& texture)
{
	bind(texture);
	GLTextureParemeter* parameters;
	size_t parametersSize;
	texture.getTextureParameters(parameters, parametersSize);

	for (size_t i = 0; i < parametersSize; i++) {
		const GLTextureParemeter& param = parameters[i];
		switch (param.name)
		{
		case GL_TEXTURE_MIN_FILTER:
		case GL_TEXTURE_MAG_FILTER:
			glTexParameteri(texture.textureType, param.name, param.value.iValue);
			break;
		default:
			LOG_ERROR << "Renderer::updateTextureParameters unsupported texture parameter " << param.name;
			break;
		}
	}
}

void Reborn::Renderer::setFramebufferTexture(Framebuffer& fbo, GLTexture& texture, GLenum attachment)
{
	bind(fbo);
	bind(texture);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.id, 0);
}

void Reborn::Renderer::setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, GLenum attachment)
{
	bind(fbo);
	bind(rbo);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo.id);
}

void Reborn::Renderer::bind(VertexBufferObject& vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
}

void Reborn::Renderer::bind(VertexArrayObject& vao)
{
	glBindVertexArray(vao.id);
}

void Reborn::Renderer::bind(Framebuffer& fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
}

void Reborn::Renderer::bindMainFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Reborn::Renderer::bind(GLTexture& texture)
{
	glBindTexture(texture.textureType, texture.id);
}

void Reborn::Renderer::bind(Renderbuffer& rbo)
{
	glBindRenderbuffer(GL_RENDERBUFFER, rbo.id);
}

bool Reborn::Renderer::isFramebufferComplete(Framebuffer& fbo)
{
	bind(fbo);
	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_UNDEFINED) {
		LOG_ERROR << "GL_FRAMEBUFFER_UNDEFINED is returned if the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT is returned if any of the framebuffer attachment points are framebuffer incomplete.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT is returned if the framebuffer does not have at least one image attached to it.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.";
	}
	if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
		LOG_ERROR << "GL_FRAMEBUFFER_UNSUPPORTED is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES.";
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS) {
		LOG_ERROR << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.";
	}

	return status == GL_FRAMEBUFFER_COMPLETE;
}

void Reborn::Renderer::destroy(Framebuffer& fbo)
{
	glDeleteFramebuffers(1, &(fbo.id));
}

void Reborn::Renderer::destroy(GLSLProgram& program)
{
	glDeleteProgram(program.id);
	program.id = -1;
}

void Reborn::Renderer::useProgram(const GLSLProgram& program)
{
	glUseProgram(program.id);
}

const Reborn::GLTexture& Reborn::Renderer::getSceneTexture()
{
	return colorAttachmentTexture;
}

void Reborn::Renderer::setClearColor(const Vector3& color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

const Reborn::Vector2& Reborn::Renderer::getSceneFraimbufferSize()
{
	return sceneFraimbufferSize;
}

void Reborn::Renderer::setSceneFramebufferSize(const Vector2& newSize)
{
	sceneFraimbufferSize = newSize;
	colorAttachmentTexture.width = newSize.x;
	colorAttachmentTexture.height = newSize.y;
	bind(colorAttachmentTexture);
	upload(colorAttachmentTexture, nullptr);

	depthStencilRenderbuffer.width = newSize.x;
	depthStencilRenderbuffer.height = newSize.y;
	bind(depthStencilRenderbuffer);
	upload(depthStencilRenderbuffer);
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