#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include <Math/MathUtils.h>

GLuint compileShader(const std::string& source, GLenum type);

std::string postprocessVertex =
#include "shaders/postprocess/postprocessVertex.glsl"
;

std::string postprocessFragment =
#include "shaders/postprocess/postprocessFragment.glsl"
;


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
		//LOG_DEBUG << "GL CALLBACK: type = " << type << ", severity = " << severity << ", message = " << message;
	}
}

Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize):
	_context(window.createGLContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
	initImGui(&window.getSDLWindow());

	auto glVersion = glGetString(GL_VERSION);
	auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	LOG_INFO << "using OpenGL " << glVersion;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glMessageCallback, 0);
	
	GLTexture colorAttachmentTexture;
	colorAttachmentTexture.width = sceneFraimbufferSize.x;
	colorAttachmentTexture.height = sceneFraimbufferSize.y;
	colorAttachmentTexture.textureType = GL_TEXTURE_2D;
	colorAttachmentTexture.internalFromat = GL_RGB;
	colorAttachmentTexture.texelFormat = GL_RGB;
	colorAttachmentTexture.texelType = GL_UNSIGNED_BYTE;
	colorAttachmentTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	colorAttachmentTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	colorAttachmentTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	colorAttachmentTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	sceneFraimbuffer.useAttachment(FramebufferAttachmentType::colorAttachment0, colorAttachmentTexture);

	GLTexture outlinedGeomTexture;
	outlinedGeomTexture.width = sceneFraimbufferSize.x;
	outlinedGeomTexture.height = sceneFraimbufferSize.y;
	outlinedGeomTexture.textureType = GL_TEXTURE_2D;
	outlinedGeomTexture.internalFromat = GL_RGB;
	outlinedGeomTexture.texelFormat = GL_RGB;
	outlinedGeomTexture.texelType = GL_UNSIGNED_BYTE;
	outlinedGeomTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	outlinedGeomTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	outlinedGeomTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	outlinedGeomTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	sceneFraimbuffer.useAttachment(FramebufferAttachmentType::colorAttachment1, outlinedGeomTexture);

	Renderbuffer depthStencilRenderbuffer;
	depthStencilRenderbuffer.width = sceneFraimbufferSize.x;
	depthStencilRenderbuffer.height = sceneFraimbufferSize.y;
	depthStencilRenderbuffer.internalFormat = GL_DEPTH24_STENCIL8;
	sceneFraimbuffer.useAttachment(FramebufferAttachmentType::depthStensilAttachment, depthStencilRenderbuffer);

	create(sceneFraimbuffer);
	if (!isFramebufferComplete(sceneFraimbuffer)) {
		LOG_ERROR << "scene framebuffer is not complete";
	}

	GLTexture postprocessTexture;
	postprocessTexture.width = sceneFraimbufferSize.x;
	postprocessTexture.height = sceneFraimbufferSize.y;
	postprocessTexture.textureType = GL_TEXTURE_2D;
	postprocessTexture.internalFromat = GL_RGB;
	postprocessTexture.texelFormat = GL_RGB;
	postprocessTexture.texelType = GL_UNSIGNED_BYTE;
	postprocessTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	postprocessTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	postprocessTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	postprocessTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	postprocessFramebuffer.useAttachment(FramebufferAttachmentType::colorAttachment0, postprocessTexture);

	create(postprocessFramebuffer);
	if (!isFramebufferComplete(postprocessFramebuffer)) {
		LOG_ERROR << "postprocess framebuffer is not complete";
	}

	bindMainFramebuffer();

	uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
	Vector3 vertices[] = {
		Vector3(-1,-1, 0),
		Vector3( 1,-1, 0),
		Vector3( 1, 1, 0),
		Vector3(-1, 1, 0)
	};
	Vector2 uv1[] = {
		Vector2(0,0),
		Vector2(1,0),
		Vector2(1,1),
		Vector2(0,1)
	};
	Mesh screenQuad(
		6,
		indices,
		4,
		vertices,
		nullptr,
		uv1
	);
	screenQuadVAO = screenQuad.getVAO();
	uint32_t* p = (uint32_t*)screenQuadVAO.ebo.data;
	create(screenQuadVAO);


	postprocessPropgram = GLSLProgram(postprocessVertex, postprocessFragment);
	create(postprocessPropgram);
}

void Reborn::Renderer::beginFrame()
{
	bind(sceneFraimbuffer);
	glViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	Vector4 clearColor0( 0.2, 0.2, 0.2, 1);
	glClearBufferfv(GL_COLOR, 0, clearColor0.d);
	Vector4 clearColor1( 0, 0, 0, 1 );
	glClearBufferfv(GL_COLOR, 1, clearColor1.d);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

bool p_open = true;

void Reborn::Renderer::endFrame()
{
	bind(postprocessFramebuffer);

	useProgram(postprocessPropgram);
	glActiveTexture(GL_TEXTURE0);
	bind(sceneFraimbuffer.colorAttachment1.value.texture);
	setUniform(postprocessPropgram, "uTexture", 0);
	glActiveTexture(GL_TEXTURE1);
	bind(sceneFraimbuffer.colorAttachment0.value.texture);
	setUniform(postprocessPropgram, "uScreenTexture", 1);
	Vector2 textureSize(sceneFraimbuffer.colorAttachment1.value.texture.width, sceneFraimbuffer.colorAttachment1.value.texture.height);
	setUniform(postprocessPropgram, "uTexelSize", Vector2(1.0, 1.0)/textureSize*2.0);
	setUniform(postprocessPropgram, "uOutlineColor", outlineColor);
	drawVAO(screenQuadVAO);
	
	bindMainFramebuffer();
	glViewport(0, 0, _window.width(), _window.height());
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(&(_window.getSDLWindow()));
}

void Reborn::Renderer::drawVAO(const VertexArrayObject& vao, GLuint offset)
{
	bind(vao);
	glDrawElements(GL_TRIANGLES, vao.ebo.size, GL_UNSIGNED_INT, (void*)offset);
}

void Reborn::Renderer::drawMesh(const Mesh& mesh)
{
	drawVAO(mesh.getVAO());
}

const SDL_GLContext& Reborn::Renderer::getContext()
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

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const int& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform1i(location, value);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const float& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform1f(location, value);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector2& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform2f(location, value.x, value.y);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector3& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Vector4& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix2& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix2fv(location, 1, transpose, value._d);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix3& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix3fv(location, 1, transpose, value._d);
}

void Reborn::Renderer::setUniform(const GLSLProgram& program, const GLchar* name, const Matrix4& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix4fv(location, 1, transpose, value._d);
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

void Reborn::Renderer::create(BufferObject& buf)
{
	glGenBuffers(1, &(buf.id));
}

void Reborn::Renderer::create(Framebuffer& fbo)
{
	glGenFramebuffers(1, &(fbo.id));
	bind(fbo);
	std::vector<GLenum> drawAttachments;
	drawAttachments.reserve(4);
	if (create(fbo.colorAttachment0)) {
		attach(fbo, fbo.colorAttachment0);		
		drawAttachments.push_back(GL_COLOR_ATTACHMENT0);
	}
	if (create(fbo.colorAttachment1)) {
		attach(fbo, fbo.colorAttachment1);
		drawAttachments.push_back(GL_COLOR_ATTACHMENT1);
	}
	if (create(fbo.colorAttachment2)) {
		attach(fbo, fbo.colorAttachment2);
		drawAttachments.push_back(GL_COLOR_ATTACHMENT2);
	}
	if (create(fbo.depthStensilAttachment)) {
		attach(fbo, fbo.depthStensilAttachment);
	}

	int s = drawAttachments.size();
	glDrawBuffers(drawAttachments.size(), drawAttachments.data());
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

	create(vao.ebo);
	bind(vao.ebo);
	upload(vao.ebo);

	for (int i = 0; i < vao.layout.size(); i++) {
		auto& attrib = vao.layout[i];
		glEnableVertexAttribArray(attrib.index);
		glVertexAttribPointer(
			attrib.index, 
			attrib.size,
			attrib.type, 
			attrib.normalized,
			attrib.stride, 
			(void*)(attrib.offset * sizeof(float)));
	}
}

void Reborn::Renderer::create(GLTexture& texture)
{
	glGenTextures(1, &(texture.id));
}

void Reborn::Renderer::upload(BufferObject& buf, GLenum usage)
{
	bind(buf);
	glBufferData(buf.type, buf.byteSize, buf.data, usage);
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
		case GL_TEXTURE_WRAP_S:
		case GL_TEXTURE_WRAP_T:
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

void Reborn::Renderer::bind(const BufferObject& buf)
{
	glBindBuffer(buf.type, buf.id);
}

void Reborn::Renderer::bind(const VertexArrayObject& vao)
{
	glBindVertexArray(vao.id);
}

void Reborn::Renderer::bind(const Framebuffer& fbo)
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

void Reborn::Renderer::destroy(VertexArrayObject& vao)
{
	glDeleteBuffers(1, &vao.vbo.id);
	glDeleteVertexArrays(1, &vao.id);
}

void Reborn::Renderer::useProgram(const GLSLProgram& program)
{
	glUseProgram(program.id);
}

const Reborn::GLTexture& Reborn::Renderer::getSceneTexture()
{
	return postprocessFramebuffer.colorAttachment0.value.texture;
}

void Reborn::Renderer::setClearColor(const Vector3& color)
{
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);
	bind(sceneFraimbuffer);
	GLfloat clearColor[] = { color.r, color.g, color.b, 1.0f };
	glClearBufferfv(GL_COLOR, 0, clearColor);
}

const Reborn::Vector2& Reborn::Renderer::getSceneFraimbufferSize()
{
	return sceneFraimbufferSize;
}

void Reborn::Renderer::setSceneFramebufferSize(const Vector2& newSize)
{
	sceneFraimbufferSize = newSize;
	sceneFraimbuffer.colorAttachment0.value.texture.width = newSize.x;
	sceneFraimbuffer.colorAttachment0.value.texture.height = newSize.y;
	bind(sceneFraimbuffer.colorAttachment0.value.texture);
	upload(sceneFraimbuffer.colorAttachment0.value.texture, nullptr);

	sceneFraimbuffer.colorAttachment1.value.texture.width = newSize.x;
	sceneFraimbuffer.colorAttachment1.value.texture.height = newSize.y;
	bind(sceneFraimbuffer.colorAttachment1.value.texture);
	upload(sceneFraimbuffer.colorAttachment1.value.texture, nullptr);

	sceneFraimbuffer.depthStensilAttachment.value.renderbuffer.width = newSize.x;
	sceneFraimbuffer.depthStensilAttachment.value.renderbuffer.height = newSize.y;
	bind(sceneFraimbuffer.depthStensilAttachment.value.renderbuffer);
	upload(sceneFraimbuffer.depthStensilAttachment.value.renderbuffer);

	postprocessFramebuffer.colorAttachment0.value.texture.width = newSize.x;
	postprocessFramebuffer.colorAttachment0.value.texture.height = newSize.y;
	bind(postprocessFramebuffer.colorAttachment0.value.texture);
	upload(postprocessFramebuffer.colorAttachment0.value.texture, nullptr);
}

Reborn::Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(_context);
}

bool Reborn::Renderer::create(FramebufferAttachment& fboAttachment)
{
	if (fboAttachment.attachment == FramebufferAttachmentType::emptyAttachment) {
		return false;
	}

	if (fboAttachment.type == GL_TEXTURE_2D) {
		create(fboAttachment.value.texture);
		bind(fboAttachment.value.texture);
		upload(fboAttachment.value.texture, NULL);
		updateTextureParameters(fboAttachment.value.texture);
	}
	else if(fboAttachment.type == GL_RENDERBUFFER) {
		create(fboAttachment.value.renderbuffer);
		bind(fboAttachment.value.renderbuffer);
		upload(fboAttachment.value.renderbuffer);
		return true;
	}
	else {
		LOG_ERROR << "Reborn::Renderer::create invalid attachment type " << fboAttachment.type;
		return false;
	}

	return true;
}

void Reborn::Renderer::attach(Framebuffer& fbo, FramebufferAttachment& fboAttachment) {
	if (fboAttachment.attachment == FramebufferAttachmentType::emptyAttachment) {
		return;
	}
	bind(fbo);
	if (fboAttachment.type == GL_TEXTURE_2D) {
		setFramebufferTexture(fbo, fboAttachment.value.texture, fboAttachment.attachment);
	}
	else if (fboAttachment.type == GL_RENDERBUFFER) {
		setFramebufferRenderbuffer(fbo, fboAttachment.value.renderbuffer, fboAttachment.attachment);
	}
	else {
		LOG_ERROR << "Reborn::Renderer::attach invalid attachment type " << fboAttachment.type;
	}
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