#pragma once
#include "Core.h"
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#if REBORN_RENDER_BACKEND_OPENGL
#include "backends/imgui_impl_opengl3.h"
#else 
static_assert(0, "no render backend???");
#endif
#include <Math/MathUtils.h>

Reborn::HandleAllocator<Reborn::MAX_VERTEX_BUFFERS> vertexBufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_INDEX_BUFFERS> indexBufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_VERTEX_ARRAY_OBJECTS> vertexArrayObjectHandlers;
Reborn::HandleAllocator<Reborn::MAX_TEXTURES> textureHandlers;
Reborn::HandleAllocator<Reborn::MAX_RENDERBUFFERS> renderbufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_FRAMEBUFFERS> framebufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_SHADERPROGRAMS> shaderprogramHandlers;

std::string postprocessVertex =
#include "shaders/postprocess/postprocessVertex.glsl"
;

std::string postprocessFragment =
#include "shaders/postprocess/postprocessFragment.glsl"
;




Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize):
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
	renderBackend = new RenderBackend_GL(window);
	auto& cbuffer = renderBackend->commandBuffer();
	renderBackend->commandBuffer().write(CommandBuffer::CommandType::INIT_BACKEND);
	renderBackend->processComandBuffer();
	initImGui(&window.getSDLWindow());
	
	struct ScreenQuadVertex
	{
		Vector3 pos;
		Vector2 uv;
	};
	static ScreenQuadVertex vertices[] = {
		{ Vector3(-1,-1, 0), Vector2( 0, 0) },
		{ Vector3( 1,-1, 0), Vector2( 1, 0) },
		{ Vector3( 1, 1, 0), Vector2( 1, 1) },
		{ Vector3(-1, 1, 0), Vector2( 0, 1) }
	};
	static uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };

	Handler vbo = createVertexBuffer(vertices, sizeof(ScreenQuadVertex) * 4);
	Handler ebo = createIndexBuffer(indices, sizeof(uint32_t) * 6);
	
	VertexLayout layout;
	layout
		.addAttribute(Attribute::POSITION, 3, AttributeType::FLOAT)
		.addAttribute(Attribute::UV1, 2, AttributeType::FLOAT)
		.build();

	screenQuadVAOHandler = createVertexArray(vbo, ebo, layout);

	colorAttachmentDescriptor.width = sceneFraimbufferSize.x;
	colorAttachmentDescriptor.height = sceneFraimbufferSize.y;
	colorAttachmentDescriptor.type = TextureType::TEXTURE_2D;
	colorAttachmentDescriptor.internalFormat = TextureFormat::RGB;
	colorAttachmentDescriptor.pixelFormat = PixelFormat::RGB;
	colorAttachmentDescriptor.texelType = TexelType::UNSIGNED_BYTE;
	colorAttachmentDescriptor.minFilter = TextureFilter::LINEAR;
	colorAttachmentDescriptor.magFilter = TextureFilter::LINEAR;
	colorAttachmentDescriptor.wrapS = TextureWrapping::CLAMP_TO_EDGE;
	colorAttachmentDescriptor.wrapT = TextureWrapping::CLAMP_TO_EDGE;
	colorAttachmentHandler = createTexture(colorAttachmentDescriptor);
	allocateTexture(colorAttachmentHandler, colorAttachmentDescriptor, 0);


	outlinedGeomTextureDescriptor.width = sceneFraimbufferSize.x;
	outlinedGeomTextureDescriptor.height = sceneFraimbufferSize.y;
	outlinedGeomTextureDescriptor.type = TextureType::TEXTURE_2D;
	outlinedGeomTextureDescriptor.internalFormat = TextureFormat::RGB;
	outlinedGeomTextureDescriptor.pixelFormat = PixelFormat::RGB;
	outlinedGeomTextureDescriptor.texelType = TexelType::UNSIGNED_BYTE;
	outlinedGeomTextureDescriptor.minFilter = TextureFilter::LINEAR;
	outlinedGeomTextureDescriptor.magFilter = TextureFilter::LINEAR;
	outlinedGeomTextureDescriptor.wrapS = TextureWrapping::CLAMP_TO_EDGE;
	outlinedGeomTextureDescriptor.wrapT = TextureWrapping::CLAMP_TO_EDGE;
	outlinedGeomAttachmentHandler = createTexture(outlinedGeomTextureDescriptor);
	allocateTexture(outlinedGeomAttachmentHandler, outlinedGeomTextureDescriptor, 0);

	depthStensilDescriptor.width = sceneFraimbufferSize.x;
	depthStensilDescriptor.height = sceneFraimbufferSize.y;
	depthStensilDescriptor.internalFormat = TextureFormat::DEPTH24_STENCIL8;
	depthStensilHandler = createRenderBuffer(depthStensilDescriptor);
	allocateRenderbuffer(depthStensilHandler, depthStensilDescriptor);

	framebufferHandler = createFrameBuffer();
	attachTextureToFramebuffer(
		framebufferHandler, 
		colorAttachmentHandler, 
		colorAttachmentDescriptor,
		FramebufferAttachmentType::colorAttachment0
	);
	attachTextureToFramebuffer(
		framebufferHandler, 
		outlinedGeomAttachmentHandler,
		outlinedGeomTextureDescriptor,
		FramebufferAttachmentType::colorAttachment1
	);
	attachRenderbufferToFramebuffer(
		framebufferHandler, 
		depthStensilHandler, 
		FramebufferAttachmentType::depthStensilAttachment
	);
	FramebufferAttachmentType attachments[3] = { 
		FramebufferAttachmentType::colorAttachment0,
		FramebufferAttachmentType::colorAttachment1
	};
	setFramebufferDrawbuffers(framebufferHandler, 2, attachments);


	postprocessTextureDescriptor.width = sceneFraimbufferSize.x;
	postprocessTextureDescriptor.height = sceneFraimbufferSize.y;
	postprocessTextureDescriptor.type = TextureType::TEXTURE_2D;
	postprocessTextureDescriptor.internalFormat = TextureFormat::RGB;
	postprocessTextureDescriptor.pixelFormat = PixelFormat::RGB;
	postprocessTextureDescriptor.texelType = TexelType::UNSIGNED_BYTE;
	postprocessTextureDescriptor.minFilter = TextureFilter::LINEAR;
	postprocessTextureDescriptor.magFilter = TextureFilter::LINEAR;
	postprocessTextureDescriptor.wrapS = TextureWrapping::CLAMP_TO_EDGE;
	postprocessTextureDescriptor.wrapT = TextureWrapping::CLAMP_TO_EDGE;
	postprocessTextureHandler = createTexture(postprocessTextureDescriptor);
	allocateTexture(postprocessTextureHandler, postprocessTextureDescriptor, 0);

	postprocessFramebufferHandler = createFrameBuffer();
	attachTextureToFramebuffer(
		postprocessFramebufferHandler,
		postprocessTextureHandler,
		postprocessTextureDescriptor,
		FramebufferAttachmentType::colorAttachment0
	);
	FramebufferAttachmentType attachments1[3] = {
		FramebufferAttachmentType::colorAttachment0
	};
	setFramebufferDrawbuffers(postprocessFramebufferHandler, 1, attachments1);

	postprocessProgrammHandler = createShaderProgram(postprocessVertex, postprocessFragment);

	bindFramebuffer();
	renderBackend->processComandBuffer();

#if 0 //test stuff
	sceneFraimbuffer.colorAttachment0.value.texture.id = gl_Textures[colorAttachmentHandler];
	sceneFraimbuffer.colorAttachment1.value.texture.id = gl_Textures[outlinedGeomAttachmentHandler];
	sceneFraimbuffer.depthStensilAttachment.value.texture.id = gl_Renderbuffers[depthStensilHandler];
	sceneFraimbuffer.id = gl_Framebuffers[framebufferHandler];
#endif


#if 0 //test code
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
#endif
}

void Reborn::Renderer::beginFrame()
{
	
	bindFramebuffer(framebufferHandler);
	setViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	Vector4 clearColor0( 0.2, 1, 0.2, 1);
	Vector4 clearColor1( 1, 0, 0, 1 );

	clear(FramebufferAttachmentType::colorAttachment0, true, true, clearColor);
	clear(FramebufferAttachmentType::colorAttachment1, true, true, {0, 0, 0, 1});
	renderBackend->processComandBuffer();
	glEnable(GL_DEPTH_TEST);
}

bool p_open = true;

void Reborn::Renderer::endFrame()
{
	bindFramebuffer(postprocessFramebufferHandler);

	bindShaderProgram(postprocessProgrammHandler);
	activateTexture(0);
	bindTexture(outlinedGeomAttachmentHandler, outlinedGeomTextureDescriptor);
	setUniform(postprocessProgrammHandler, "uTexture", 0);

	activateTexture(1);
	bindTexture(colorAttachmentHandler, colorAttachmentDescriptor);
	setUniform(postprocessProgrammHandler, "uScreenTexture", 1);
	Vector2 textureSize(colorAttachmentDescriptor.width, colorAttachmentDescriptor.height);
	setUniform(postprocessProgrammHandler, "uTexelSize", Vector2(1.0, 1.0)/textureSize*2.0);
	setUniform(postprocessProgrammHandler, "uOutlineColor", outlineColor);
	
	renderVAO(screenQuadVAOHandler, 6);
	bindFramebuffer();
	
	setViewport(0,0,_window.width(), _window.height());
	//clear(FramebufferAttachmentType::colorAttachment0, true, false, this->clearColor);
	renderBackend->processComandBuffer();

#if REBORN_RENDER_BACKEND_OPENGL
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#else 
	static_assert(0, "no render backend???");
#endif


#if REBORN_RENDER_BACKEND_OPENGL
	SDL_GL_SwapWindow(&(_window.getSDLWindow()));
#else 
	static_assert(0, "no render backend???");
#endif
}

Reborn::RenderBackend& Reborn::Renderer::getRenderBackend()
{
	return *renderBackend;
}

Reborn::Camera& Reborn::Renderer::getCamera()
{
	return _camera;
}

const Reborn::Camera& Reborn::Renderer::getCamera() const
{
	return _camera;
}




Reborn::Handler Reborn::Renderer::createVertexBuffer(void* data, std::size_t sizeInBytes) {
	Reborn::Handler vertexBufferHandler = vertexBufferHandlers.allocate();
	if (vertexBufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_VERTEX_BUFFER)
			.write(vertexBufferHandler)
			.write(sizeInBytes)
			.write(data);
	}
	return vertexBufferHandler;
}

Reborn::Handler Reborn::Renderer::createIndexBuffer(void* data, std::size_t sizeInBytes) {
	Reborn::Handler indexBufferHandler = indexBufferHandlers.allocate();
	if (indexBufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_INDEX_BUFFER)
			.write(indexBufferHandler)
			.write(sizeInBytes)
			.write(data);
	}
	return indexBufferHandler;
}

Reborn::Handler Reborn::Renderer::createVertexArray(
	const Reborn::Handler& vertexBufferHandler,
	const Reborn::Handler& indexBufferHandler,
	const Reborn::VertexLayout& layout
) {
	Reborn::Handler vertexArrayHandler = vertexArrayObjectHandlers.allocate();
	const uint16_t numAttributes = layout.getAttributes().size();
	if (vertexArrayHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_VERTEX_ARRAY_OBJECT)
			.write(vertexArrayHandler)
			.write(vertexBufferHandler)
			.write(indexBufferHandler)
			.write(numAttributes);
		for (uint16_t i = 0; i < numAttributes; i++) {
			renderBackend->commandBuffer().write(layout.getAttributes()[i]);
		}
	}
	return vertexArrayHandler;
}

Reborn::Handler Reborn::Renderer::createTexture(const Reborn::TextureDescriptor& descriptor) {
	Reborn::Handler textureHandler = textureHandlers.allocate();
	if (textureHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_TEXTURE)
			.write(textureHandler)
			.write(descriptor);
	}
	return textureHandler;
}

Reborn::Handler Reborn::Renderer::createRenderBuffer(const Reborn::RenderbufferDescriptor& descriptor) {
	Reborn::Handler renderbufferHandler = renderbufferHandlers.allocate();
	if (renderbufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_RENDERBUFFER)
			.write(renderbufferHandler)
			.write(descriptor);
	}
	return renderbufferHandler;
}

Reborn::Handler Reborn::Renderer::createFrameBuffer() {
	Reborn::Handler framebufferHandler = framebufferHandlers.allocate();
	if (framebufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_FRAMEBUFFER)
			.write(framebufferHandler);
	}
	return framebufferHandler;
}

Reborn::Handler Reborn::Renderer::createShaderProgram(
	const std::string& vertexSource, 
	const std::string& fragmentSource
) {
	Reborn::Handler shaderProgramHandler = shaderprogramHandlers.allocate();
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::CREATE_SHADER_PROGRAM)
			.write(shaderProgramHandler)
			.writeString(vertexSource)
			.writeString(fragmentSource);
	}
	return shaderProgramHandler;
}

void Reborn::Renderer::deleteSharerProgram(Handler handler)
{
	if (handler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::DELETE_SHADER_PROGRAM)
			.write(handler);
		shaderprogramHandlers.free(handler);
	}
}

void Reborn::Renderer::allocateTexture(
	Handler textureHandler, 
	const Reborn::TextureDescriptor& descriptor, 
	uint16_t mipLevel,
	void* data
) {
	if (textureHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::ALLOCATE_TEXTURE)
			.write(textureHandler)
			.write(descriptor)
			.write(mipLevel)
			.write(data);
	}
}

void Reborn::Renderer::allocateRenderbuffer(Reborn::Handler handler, const Reborn::RenderbufferDescriptor& descriptor) {
	if (handler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::ALLOCATE_RENDERBUFFER)
			.write(handler)
			.write(descriptor);
	}
}

void Reborn::Renderer::attachTextureToFramebuffer(
	Reborn::Handler framebufferHandler, 
	Reborn::Handler textureHandler, 
	const Reborn::TextureDescriptor& textureDescriptor,
	const Reborn::FramebufferAttachmentType& attachment) {
	if (framebufferHandler != Reborn::InvalidHandle && textureHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::ATTACH_TEXTURE_TO_FRAMEBUFFER)
			.write(framebufferHandler)
			.write(textureHandler)
			.write(textureDescriptor)
			.write(attachment);
	}
}

void Reborn::Renderer::attachRenderbufferToFramebuffer(
	Reborn::Handler framebufferHandler, 
	Reborn::Handler renderbufferHandler, 
	const Reborn::FramebufferAttachmentType& attachment) {
	if (framebufferHandler != Reborn::InvalidHandle && renderbufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::ATTACH_RENDERBUFFER_TO_FRAMEBUFFER)
			.write(framebufferHandler)
			.write(renderbufferHandler)
			.write(attachment);
	}
}

void Reborn::Renderer::setFramebufferDrawbuffers(
	Reborn::Handler framebufferHandler, 
	uint8_t numAttachments, 
	Reborn::FramebufferAttachmentType attachments[3]
) {
	assert(numAttachments <=3, "don't expect more than 3 attachments");
	if (framebufferHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_FRAMEBUFFER_DRAWBUFFERS)
			.write(framebufferHandler)
			.write(numAttachments);

		for (uint8_t i = 0; i < numAttachments; i++) {
			renderBackend->commandBuffer().write(attachments[i]);
		}
	}
}

void Reborn::Renderer::bindFramebuffer(Handler framebufferHandler) {
	renderBackend->commandBuffer()
		.write(Reborn::CommandBuffer::CommandType::BIND_FRAMEBUFFER)
		.write(framebufferHandler);
}

void Reborn::Renderer::bindTexture(Reborn::Handler textureHandler, const Reborn::TextureDescriptor& descriptor) {
	if (textureHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::BIND_TEXTURE)
			.write(textureHandler)
			.write(descriptor);
	}
}

void Reborn::Renderer::bindShaderProgram(Reborn::Handler shaderProgramHandler) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::BIND_SHADER_PROGRAM)
			.write(shaderProgramHandler);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const int& value
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::INT)
			.write(value);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const float& value
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::FLOAT)
			.write(value);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Reborn::Vector2& value
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::VECTOR2F)
			.write(value);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Vector3& value
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::VECTOR3F)
			.write(value);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Vector4& value
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::VECTOR4F)
			.write(value);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Matrix2& value,
	bool transpose
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::MATRIX2F)
			.write(value)
			.write(transpose);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Matrix3& value,
	bool transpose
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::MATRIX3F)
			.write(value)
			.write(transpose);
	}
}

void Reborn::Renderer::setUniform(
	Reborn::Handler shaderProgramHandler, 
	const std::string& name, 
	const Matrix4& value,
	bool transpose
) {
	if (shaderProgramHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE)
			.write(shaderProgramHandler)
			.write(name.length())
			.write(name.data(), name.length())
			.write(UniformValueType::MATRIX4F)
			.write(value)
			.write(transpose);
	}
}

void Reborn::Renderer::activateTexture(int attachmentIndex) {
	renderBackend->commandBuffer()
		.write(Reborn::CommandBuffer::CommandType::ACTIVATE_TEXTURE)
		.write(attachmentIndex);
}

void Reborn::Renderer::renderVAO(Handler vaoHandler, uint32_t count, uint32_t offset) {
	if (vaoHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::RENDER_VAO)
			.write(vaoHandler)
			.write(count)
			.write(offset);
	}
}

void Reborn::Renderer::setViewport(uint16_t x, uint16_t y, uint16_t with, uint16_t height) {
	renderBackend->commandBuffer()
		.write(Reborn::CommandBuffer::CommandType::SET_VIEWPORT)
		.write(x)
		.write(y)
		.write(with)
		.write(height);
}

void Reborn::Renderer::clear(
	FramebufferAttachmentType bufferToClear,
	bool clearColor,
	bool cleatDepth, 
	Vector4 color
) {
	renderBackend->commandBuffer()
		.write(Reborn::CommandBuffer::CommandType::CLEAR_VIEWPORT)
		.write(bufferToClear)
		.write(clearColor)
		.write(cleatDepth)
		.write(color);
		
}

void Reborn::Renderer::create(GLTexture& texture)
{
	glGenTextures(1, &(texture.id));
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

void Reborn::Renderer::bind(GLTexture& texture)
{
	glBindTexture(texture.textureType, texture.id);
}

void Reborn::Renderer::destroy(GLSLProgram& program)
{
	//glDeleteProgram(program.id);
	program.id = -1;
}

const Reborn::GLTexture& Reborn::Renderer::getSceneTexture()
{
	//return postprocessFramebuffer.colorAttachment0.value.texture;
	static GLTexture res = GLTexture();
	res.width = postprocessTextureDescriptor.width;
	res.height = postprocessTextureDescriptor.height;
	res.id = InvalidHandle;
#if REBORN_RENDER_BACKEND_OPENGL
	res.id = static_cast<Reborn::RenderBackend_GL*>(renderBackend)->gl_Textures[postprocessTextureHandler];
#endif
	return res;
}

void Reborn::Renderer::setClearColor(const Vector3& _clearColor)
{
	this->clearColor = Vector4(_clearColor.xyz, 1);
}

const Reborn::Vector2& Reborn::Renderer::getSceneFraimbufferSize()
{
	return sceneFraimbufferSize;
}

void Reborn::Renderer::setSceneFramebufferSize(const Vector2& newSize)
{
	sceneFraimbufferSize = newSize;
	colorAttachmentDescriptor.width = newSize.x;
	colorAttachmentDescriptor.height = newSize.y;
	bindTexture(colorAttachmentHandler, colorAttachmentDescriptor);  
	allocateTexture(colorAttachmentHandler, colorAttachmentDescriptor, 0);

	outlinedGeomTextureDescriptor.width = newSize.x;
	outlinedGeomTextureDescriptor.height = newSize.y;
	bindTexture(outlinedGeomAttachmentHandler, outlinedGeomTextureDescriptor);
	allocateTexture(outlinedGeomAttachmentHandler, outlinedGeomTextureDescriptor, 0);

	depthStensilDescriptor.width = newSize.x;
	depthStensilDescriptor.height = newSize.y;
	allocateRenderbuffer(depthStensilHandler, depthStensilDescriptor);

	postprocessTextureDescriptor.width = newSize.x;
	postprocessTextureDescriptor.height = newSize.y;
	allocateTexture(postprocessTextureHandler, postprocessTextureDescriptor, 0);
	renderBackend->processComandBuffer();
}

Reborn::Renderer::~Renderer()
{
#if REBORN_RENDER_BACKEND_OPENGL
	ImGui_ImplOpenGL3_Shutdown();
#else 
	static_assert(0, "no render backend???");
#endif
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete renderBackend;
}

bool Reborn::Renderer::initImGui(SDL_Window* window) {



	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
#if REBORN_RENDER_BACKEND_OPENGL
	ImGui_ImplSDL2_InitForOpenGL(window, renderBackend->getContext().OpenGL_Handler);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
#else 
	static_assert(0, "no render backend???");
#endif
	return true;
}