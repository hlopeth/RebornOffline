#include <Core.h>
#include <glad/glad.h>
#include "GLRenderer.h"
#include "backends/imgui_impl_opengl3.h"
#include <backends/imgui_impl_sdl.h>
#include <Math/MathUtils.h>

GLuint compileShader(const std::string& source, GLenum type);

std::string postprocessVertex =
#include "Graphics/shaders/postprocess/postprocessVertex.glsl"
;

std::string postprocessFragment =
#include "Graphics/shaders/postprocess/postprocessFragment.glsl"
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

namespace Reborn
{
	GLRenderer::GLRenderer(Window& window, const Vector2& sceneFraimbufferSize) :
		Renderer(window, sceneFraimbufferSize, API_TYPE),
		context(window.createRenderingContext())
	{
		if (!gladLoadGL()) {
			LOG_ERROR << "ImGuiSystem::init Failed to init glad";
			return;
		}

		auto glVersion = glGetString(GL_VERSION);
		auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

		LOG_INFO << "using OpenGL " << glVersion;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(glMessageCallback, 0);

		GLTextureHandler colorAttachmentTexture(sceneFraimbufferSize);
		colorAttachmentTexture.textureType = GL_TEXTURE_2D;
		colorAttachmentTexture.internalFromat = GL_RGB;
		colorAttachmentTexture.texelFormat = GL_RGB;
		colorAttachmentTexture.texelType = GL_UNSIGNED_BYTE;
		colorAttachmentTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		colorAttachmentTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		colorAttachmentTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		colorAttachmentTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		sceneFraimbuffer.useAttachment(GLFramebufferAttachmentType::colorAttachment0, colorAttachmentTexture);

		GLTextureHandler outlinedGeomTexture(sceneFraimbufferSize);
		outlinedGeomTexture.textureType = GL_TEXTURE_2D;
		outlinedGeomTexture.internalFromat = GL_RGB;
		outlinedGeomTexture.texelFormat = GL_RGB;
		outlinedGeomTexture.texelType = GL_UNSIGNED_BYTE;
		outlinedGeomTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		outlinedGeomTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		outlinedGeomTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		outlinedGeomTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		sceneFraimbuffer.useAttachment(GLFramebufferAttachmentType::colorAttachment1, outlinedGeomTexture);

		GLRenderbuffer depthStencilRenderbuffer(sceneFraimbufferSize, GL_DEPTH24_STENCIL8);
		//depthStencilRenderbuffer.width = sceneFraimbufferSize.x;
		//depthStencilRenderbuffer.height = sceneFraimbufferSize.y;
		//depthStencilRenderbuffer.internalFormat = GL_DEPTH24_STENCIL8;
		sceneFraimbuffer.useAttachment(GLFramebufferAttachmentType::depthStensilAttachment, depthStencilRenderbuffer);

		create(sceneFraimbuffer);
		if (!isFramebufferComplete(sceneFraimbuffer)) {
			LOG_ERROR << "scene framebuffer is not complete";
		}

		GLTextureHandler postprocessTexture(sceneFraimbufferSize);
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
			Vector3(1,-1, 0),
			Vector3(1, 1, 0),
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


		postprocessPropgram = GLShaderProgram(postprocessVertex, postprocessFragment);
		create(postprocessPropgram);
	}
}

void Reborn::GLRenderer::beginFrame()
{
	bind(sceneFraimbuffer);
	glViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	Vector4 clearColor0(0.2, 0.2, 0.2, 1);
	glClearBufferfv(GL_COLOR, 0, clearColor0.d);
	Vector4 clearColor1(0, 0, 0, 1);
	glClearBufferfv(GL_COLOR, 1, clearColor1.d);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

bool p_open = true;

void Reborn::GLRenderer::endFrame(ImGuiManager& imguiManager)
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
	setUniform(postprocessPropgram, "uTexelSize", Vector2(1.0, 1.0) / textureSize * 2.0);
	setUniform(postprocessPropgram, "uOutlineColor", outlineColor);
	drawVAO(screenQuadVAO);

	bindMainFramebuffer();
	glViewport(0, 0, _window.width(), _window.height());
	glClear(GL_COLOR_BUFFER_BIT);

	imguiManager.render();

	SDL_GL_SwapWindow(&(_window.getSDLWindow()));
}

void Reborn::GLRenderer::drawVAO(const VertexArrayObject& vao, UIntValue offset)
{
	bind(vao);
	glDrawElements(GL_TRIANGLES, vao.ebo.size, GL_UNSIGNED_INT, (void*)offset);
}

const RenderingContext& Reborn::GLRenderer::getContext()
{
	return context;
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const CharValue* name, const float& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform1f(location, value);
}


void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const int& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform1i(location, value);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Vector2& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform2f(location, value.x, value.y);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Vector3& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Vector4& value)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Matrix2& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix2fv(location, 1, transpose, value._d);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Matrix3& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix3fv(location, 1, transpose, value._d);
}

void Reborn::GLRenderer::setUniform(const GLShaderProgram& program, const GLchar* name, const Matrix4& value, bool transpose)
{
	GLuint location = glGetUniformLocation(program.id, name);
	glUniformMatrix4fv(location, 1, transpose, value._d);
}


bool Reborn::Renderer::initImGui(SDL_Window* window) {
	ImGui_ImplSDL2_InitForOpenGL(window, _context);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	return true;
}

void Reborn::Renderer::newImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
}

void Reborn::Renderer::drawImGui(ImDrawData* drawData)
{
	ImGui_ImplOpenGL3_RenderDrawData(drawData);
}

void Reborn::Renderer::destroyImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
}