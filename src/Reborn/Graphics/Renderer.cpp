#pragma once
#include "Core.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include <Math/MathUtils.h>

Reborn::HandleAllocator<Reborn::MAX_VERTEX_BUFFERS> vertexBufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_INDEX_BUFFERS> indexBufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_VERTEX_ARRAY_OBJECTS> vertexArrayObjectHandlers;
Reborn::HandleAllocator<Reborn::MAX_TEXTURES> textureHandlers;
Reborn::HandleAllocator<Reborn::MAX_RENDERBUFFERS> renderbufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_FRAMEBUFFERS> framebufferHandlers;
Reborn::HandleAllocator<Reborn::MAX_SHADERPROGRAMS> shaderprogramHandlers;

GLuint compileShader(const std::string& source, GLenum type);

std::string postprocessVertex =
#include "shaders/postprocess/postprocessVertex.glsl"
;

std::string postprocessFragment =
#include "shaders/postprocess/postprocessFragment.glsl"
;


//TEMP RenderBackend_GL.cpp
namespace Reborn {

	GLuint gl_vertexBuffers[MAX_VERTEX_BUFFERS];
	GLuint gl_indexBuffers[MAX_INDEX_BUFFERS];
	GLuint gl_vertexArrayObjects[MAX_VERTEX_ARRAY_OBJECTS];
	GLuint gl_Textures[MAX_TEXTURES];
	GLuint gl_Renderbuffers[MAX_RENDERBUFFERS];
	GLuint gl_Framebuffers[MAX_FRAMEBUFFERS];
	GLuint gl_ShaderPrograms[MAX_SHADERPROGRAMS];

	GLenum toGLType(AttributeType type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::AttributeType::FLOAT:
			result = GL_FLOAT;
			break;
		case Reborn::AttributeType::COUNT:
		default:
			assert(0,"unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(FramebufferAttachmentType attachmentType) {
		GLenum result = 0;
		switch (attachmentType)
		{
		case Reborn::FramebufferAttachmentType::colorAttachment0:
			result = GL_COLOR_ATTACHMENT0;
			break;
		case Reborn::FramebufferAttachmentType::colorAttachment1:
			result = GL_COLOR_ATTACHMENT1;
			break;
		case Reborn::FramebufferAttachmentType::colorAttachment2:
			result = GL_COLOR_ATTACHMENT2;
			break;
		case Reborn::FramebufferAttachmentType::depthStensilAttachment:
			result = GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		case Reborn::FramebufferAttachmentType::emptyAttachment:
		default:
			assert(0, "wtf");
			break;
		}
		return result;
	}

	GLenum toGLType(TextureType type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::TextureType::TEXTURE_2D:
			result = GL_TEXTURE_2D;
			break;
		case Reborn::TextureType::COUNT:
		default:
			assert(0,"unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(TextureFormat type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::TextureFormat::RGB:
			result = GL_RGB;
			break;
		case Reborn::TextureFormat::RGBA:
			result = GL_RGBA;
			break;
		case Reborn::TextureFormat::DEPTH24_STENCIL8:
			result = GL_DEPTH24_STENCIL8;
			break;
		case Reborn::TextureFormat::COUNT:
		default:
			assert(0, "unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(PixelFormat type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::PixelFormat::RGB:
			result = GL_RGB;
			break;
		case Reborn::PixelFormat::RGBA:
			result = GL_RGBA;
			break;
		case Reborn::PixelFormat::COUNT:
		default:
			assert(0, "unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(TexelType type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::TexelType::UNSIGNED_BYTE:
			result = GL_UNSIGNED_BYTE;
			break;
		case Reborn::TexelType::COUNT:
		default:
			assert(0, "unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(TextureFilter type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::TextureFilter::NEAREST:
			result = GL_NEAREST;
			break;
		case Reborn::TextureFilter::LINEAR:
			result = GL_LINEAR;
			break;
		case Reborn::TextureFilter::NEAREST_MIPMAP_NEAREST:
			result = GL_NEAREST_MIPMAP_NEAREST;
			break;
		case Reborn::TextureFilter::LINEAR_MIPMAP_NEAREST:
			result = GL_LINEAR_MIPMAP_NEAREST;
			break;
		case Reborn::TextureFilter::LINEAR_MIPMAP_LINEAR:
			result = GL_LINEAR_MIPMAP_LINEAR;
			break;
		case Reborn::TextureFilter::COUNT:
		default:
			assert(0, "unknown type");
			break;
		}
		return result;
	}

	GLenum toGLType(TextureWrapping type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::TextureWrapping::CLAMP_TO_EDGE:
			result = GL_CLAMP_TO_EDGE;
			break;
		case Reborn::TextureWrapping::CLAMP_TO_BORDER:
			result = GL_CLAMP_TO_BORDER;
			break;
		case Reborn::TextureWrapping::MIRRORED_REPEAT:
			result = GL_MIRRORED_REPEAT;
			break;
		case Reborn::TextureWrapping::REPEAT:
			result = GL_REPEAT;
			break;
		case Reborn::TextureWrapping::MIRROR_CLAMP_TO_EDGE:
			result = GL_MIRROR_CLAMP_TO_EDGE;
			break;
		case Reborn::TextureWrapping::COUNT:
		default:
			assert(0, "unknown type");
			break;
		}
		return result;
	}

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

	enum struct UniformValueType {
		INT,
		FLOAT,
		VECTOR2F,
		VECTOR3F,
		VECTOR4F,
		MATRIX2F,
		MATRIX3F,
		MATRIX4F,
		COUNT
	};


	RenderBackend_GL::RenderBackend_GL(SDL_GLContext& _context) :
		context(_context),
		RenderBackend(BackendType::OPEN_GL)
	{

	}

	void RenderBackend_GL::processComandBuffer()
	{
		CommandBuffer::CommandType cmd;
		while (!_commandBuffer.empty()) {
			_commandBuffer.read(cmd);
			switch (cmd)
			{
			case CommandBuffer::CommandType::INIT_BACKEND:
				init();
				break;
			case CommandBuffer::CommandType::CREATE_VERTEX_BUFFER: {
				Handler handler;
				std::size_t sizeInBytes;
				void* data;
				auto usage = GL_STATIC_DRAW; // pass through command buffer
				_commandBuffer
					.read(handler)
					.read(sizeInBytes)
					.read(data);

				glGenBuffers(1, &gl_vertexBuffers[handler]);
				glBindBuffer(GL_ARRAY_BUFFER, gl_vertexBuffers[handler]);
				glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, usage);
				break;
			}
			case CommandBuffer::CommandType::CREATE_INDEX_BUFFER: {
				Handler handler;
				std::size_t sizeInBytes;
				void* data;
				auto usage = GL_STATIC_DRAW; // pass through command buffer
				_commandBuffer
					.read(handler)
					.read(sizeInBytes)
					.read(data);

				glGenBuffers(1, &gl_indexBuffers[handler]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_indexBuffers[handler]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, usage);
				break;
			}
			case CommandBuffer::CommandType::CREATE_VERTEX_ARRAY_OBJECT: {
				Handler vaoHandler;
				Handler vboHandler;
				Handler eboHandler;
				uint16_t numAttributes;
				static std::vector<VertexLayout::VertexAttribute> attributes;

				_commandBuffer
					.read(vaoHandler)
					.read(vboHandler)
					.read(eboHandler)
					.read(numAttributes);

				attributes.resize(numAttributes);
				for (uint16_t i = 0; i < numAttributes; i++) {
					_commandBuffer.read(attributes[i]);
				}

				glGenVertexArrays(1, &gl_vertexArrayObjects[vaoHandler]);
				glBindVertexArray(gl_vertexArrayObjects[vaoHandler]);
				glBindBuffer(GL_ARRAY_BUFFER, gl_vertexBuffers[vboHandler]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_indexBuffers[eboHandler]);

				for (uint16_t i = 0; i < numAttributes; i++) {
					const auto& attrib = attributes[i];
					glEnableVertexAttribArray(attrib.index);
					glVertexAttribPointer(
						attrib.index,
						attrib.size,
						toGLType(attrib.type),
						attrib.normalized,
						attrib.strideBytes,
						(void*)attrib.offsetBytes
					);
				}
				break;

			}
			case CommandBuffer::CommandType::CREATE_TEXTURE: {
				Handler textureHandler;
				TextureDescriptor descriptor;

				_commandBuffer
					.read(textureHandler)
					.read(descriptor);

				glGenTextures(1, &gl_Textures[textureHandler]);
				GLenum GLType = toGLType(descriptor.type);
				glBindTexture(GLType, gl_Textures[textureHandler]);
				glTexParameteri(GLType, GL_TEXTURE_MIN_FILTER, toGLType(descriptor.minFilter));
				glTexParameteri(GLType, GL_TEXTURE_MAG_FILTER, toGLType(descriptor.magFilter));
				glTexParameteri(GLType, GL_TEXTURE_WRAP_S, toGLType(descriptor.wrapS));
				glTexParameteri(GLType, GL_TEXTURE_WRAP_T, toGLType(descriptor.wrapT));
				break;
			}
			case CommandBuffer::CommandType::CREATE_RENDERBUFFER: {
				Handler renderbufferHandler;
				RenderbufferDescriptor descriptor;

				_commandBuffer
					.read(renderbufferHandler)
					.read(descriptor);

				glGenRenderbuffers(1, &gl_Renderbuffers[renderbufferHandler]);
				break;
			}
			case CommandBuffer::CommandType::CREATE_FRAMEBUFFER: {
				Handler framebufferHandler;

				_commandBuffer
					.read(framebufferHandler);

				glGenFramebuffers(1, &gl_Framebuffers[framebufferHandler]);
				break;
			}
			case CommandBuffer::CommandType::CREATE_SHADER_PROGRAM: {
				Handler shaderProgramHandler;
				size_t vertexSourceLength;
				std::string vertexSource;
				size_t fragmentSourceLength;
				std::string fragmentSource;
				
				_commandBuffer.read(shaderProgramHandler);

				_commandBuffer.read(vertexSourceLength);
				vertexSource.resize(vertexSourceLength, '%');
				_commandBuffer.read(vertexSource.data(), vertexSourceLength);

				_commandBuffer.read(fragmentSourceLength);
				fragmentSource.resize(fragmentSourceLength, '%');
				_commandBuffer.read(fragmentSource.data(), fragmentSourceLength);

				GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
				GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

				const GLuint shaderProgram = glCreateProgram();
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
				gl_ShaderPrograms[shaderProgramHandler] = shaderProgram;

				break;
			}
			case CommandBuffer::CommandType::ALLOCATE_TEXTURE: {
				Handler textureHandler;
				TextureDescriptor descriptor;
				uint16_t mipLevel;
				void* data;


				_commandBuffer
					.read(textureHandler)
					.read(descriptor)
					.read(mipLevel)
					.read(data);

				assert(!data, "I cannot test data upload for now");

				glBindTexture(toGLType(descriptor.type), gl_Textures[textureHandler]);
				glTexImage2D(
					toGLType(descriptor.type),
					mipLevel, 
					toGLType(descriptor.internalFormat),
					descriptor.width,
					descriptor.height,
					0,
					toGLType(descriptor.pixelFormat),
					toGLType(descriptor.texelType),
					data
				);
				break;
			}
			case CommandBuffer::CommandType::ALLOCATE_RENDERBUFFER: {
				Handler renderbufferHandler;
				RenderbufferDescriptor descriptor;

				_commandBuffer
					.read(renderbufferHandler)
					.read(descriptor);

				glBindRenderbuffer(GL_RENDERBUFFER, gl_Renderbuffers[renderbufferHandler]);
				glRenderbufferStorage(
					GL_RENDERBUFFER, 
					toGLType(descriptor.internalFormat), 
					descriptor.width, 
					descriptor.height
				);
				break;
			}
			case CommandBuffer::CommandType::ATTACH_TEXTURE_TO_FRAMEBUFFER: {
				Handler framebufferHandler;
				Handler textureHandler;
				TextureDescriptor textureDescriptor;
				FramebufferAttachmentType attachment;

				_commandBuffer
					.read(framebufferHandler)
					.read(textureHandler)
					.read(textureDescriptor)
					.read(attachment);

				glBindFramebuffer(GL_FRAMEBUFFER, gl_Framebuffers[framebufferHandler]);
				glBindTexture(toGLType(textureDescriptor.type), gl_Textures[textureHandler]);
				glFramebufferTexture2D(
					GL_FRAMEBUFFER,
					toGLType(attachment),
					toGLType(textureDescriptor.type),
					gl_Textures[textureHandler],
					0
				);
				break;
			}
			case CommandBuffer::CommandType::ATTACH_RENDERBUFFER_TO_FRAMEBUFFER: {
				Handler framebufferHandler;
				Handler renderbufferHandler;
				FramebufferAttachmentType attachment;

				_commandBuffer
					.read(framebufferHandler)
					.read(renderbufferHandler)
					.read(attachment);

				glBindFramebuffer(GL_FRAMEBUFFER, gl_Framebuffers[framebufferHandler]);
				glBindRenderbuffer(GL_RENDERBUFFER, gl_Renderbuffers[renderbufferHandler]);
				glFramebufferRenderbuffer(
					GL_FRAMEBUFFER, 
					toGLType(attachment), 
					GL_RENDERBUFFER, 
					gl_Renderbuffers[renderbufferHandler]
				);
				break;
			}
			case CommandBuffer::CommandType::SET_FRAMEBUFFER_DRAWBUFFERS: {
				Handler framebufferHandler;
				uint8_t numAttachments;
				GLenum attachments[3];

				_commandBuffer
					.read(framebufferHandler)
					.read(numAttachments);

				for (uint8_t i = 0; i < numAttachments; i++) {
					FramebufferAttachmentType attachment;
					_commandBuffer.read(attachment);
					attachments[i] = toGLType(attachment);
				}

				glBindFramebuffer(GL_FRAMEBUFFER, gl_Framebuffers[framebufferHandler]);
				glDrawBuffers(numAttachments, attachments);

				break;
			}
			case CommandBuffer::CommandType::BIND_FRAMEBUFFER: {
				Handler framebufferHandler;

				_commandBuffer
					.read(framebufferHandler);

				GLuint id = framebufferHandler == InvalidHandle ? 0 : gl_Framebuffers[framebufferHandler];
				glBindFramebuffer(GL_FRAMEBUFFER, id);
				break;
			}
			case CommandBuffer::CommandType::BIND_TEXTURE: {
				Handler textureHandler;
				TextureDescriptor descriptor;

				_commandBuffer
					.read(textureHandler)
					.read(descriptor);

				glBindTexture(toGLType(descriptor.type), gl_Textures[textureHandler]);
				break;
			}
			case CommandBuffer::CommandType::BIND_SHADER_PROGRAM: {
				Handler shaderProgramHandler;

				_commandBuffer
					.read(shaderProgramHandler);

				glUseProgram(gl_ShaderPrograms[shaderProgramHandler]);
				break;
			}
			case CommandBuffer::CommandType::SET_NAMED_UNIFORM_VALUE: {
				Handler shaderProgramHandler;
				size_t paramNameLength;
				std::string paramName;
				UniformValueType paramType;

				_commandBuffer
					.read(shaderProgramHandler)
					.read(paramNameLength);
				paramName.resize(paramNameLength, '%');
				_commandBuffer
					.read(paramName.data(), paramNameLength)
					.read(paramType);


				GLuint location = glGetUniformLocation(gl_ShaderPrograms[shaderProgramHandler], paramName.c_str());

				switch (paramType)
				{
				case Reborn::UniformValueType::INT: {
					int value;
					_commandBuffer.read(value);
					glUniform1i(location, value);
					break;
				}
				case Reborn::UniformValueType::FLOAT:
					assert(0, "wtf");
					break;
				case Reborn::UniformValueType::VECTOR2F: {
					Vector2 value;
					_commandBuffer.read(value);
					glUniform2f(location, value.x, value.y);
					break;
				}
				case Reborn::UniformValueType::VECTOR3F: {
					Vector3 value;
					_commandBuffer.read(value);
					glUniform3f(location, value.x, value.y, value.z);
					break;
				}
				case Reborn::UniformValueType::VECTOR4F:
					assert(0, "wtf");
					break;
				case Reborn::UniformValueType::MATRIX2F:
					assert(0, "wtf");
					break;
				case Reborn::UniformValueType::MATRIX3F:
					assert(0, "wtf");
					break;
				case Reborn::UniformValueType::MATRIX4F:
					assert(0, "wtf");
					break;
				case Reborn::UniformValueType::COUNT:
					assert(0, "wtf");
					break;
				default:
					break;
				}
				break;
			}
			case CommandBuffer::CommandType::ACTIVATE_TEXTURE: {
				int attachmentIndex;
				_commandBuffer.read(attachmentIndex);
				glActiveTexture(GL_TEXTURE0 + attachmentIndex);
				break;
			}
			case CommandBuffer::CommandType::RENDER_VAO: {
				Handler vaoHandler;
				uint32_t size;
				uint32_t offset;

				_commandBuffer
					.read(vaoHandler)
					.read(size)
					.read(offset);


				glBindVertexArray(gl_vertexArrayObjects[vaoHandler]);
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)offset);
				break;
			}
			case CommandBuffer::CommandType::SET_VIEWPORT: {
				uint16_t x;
				uint16_t y;
				uint16_t with;
				uint16_t height;

				_commandBuffer
					.read(x)
					.read(y)
					.read(with)
					.read(height);

				glViewport(x, y, with, height);
				break;
			}
			case CommandBuffer::CommandType::CLEAR_VIEWPORT: {
				FramebufferAttachmentType bufferToClear;
				bool shouldClearColor;
				bool shouldClearDepth;
				Vector4 clearColor;

				_commandBuffer
					.read(bufferToClear)
					.read(shouldClearColor)
					.read(shouldClearDepth)
					.read(clearColor);

				if (shouldClearColor) {
					GLuint t = GLuint(bufferToClear) - GLuint(FramebufferAttachmentType::colorAttachment0);
					glClearBufferfv(GL_COLOR, t, clearColor.d);
				}
				if (shouldClearDepth) {
					glClear(GL_DEPTH_BUFFER_BIT);
				}

				break;
			}
			default:
				assert(0, "wtf");
				break;
			}
		}
	}

	const RenderContext_Handler RenderBackend_GL::getContext() {
		RenderContext_Handler handler;
		handler.OpenGL_Handler = context;
		return handler;
	}

	void RenderBackend_GL::init() {
		auto glVersion = glGetString(GL_VERSION);
		auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

		LOG_INFO << "using OpenGL " << glVersion;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(glMessageCallback, 0);
	}
}

//END TEMP RenderBackend_GL.cpp





Reborn::Handler framebufferHandler = Reborn::InvalidHandle;
Reborn::TextureDescriptor colorAttachmentDescriptor;
Reborn::Handler colorAttachmentHandler = Reborn::InvalidHandle;
Reborn::TextureDescriptor outlinedGeomTextureDescriptor;
Reborn::Handler outlinedGeomAttachmentHandler = Reborn::InvalidHandle;
Reborn::RenderbufferDescriptor depthStensilDescriptor;
Reborn::Handler depthStensilHandler = Reborn::InvalidHandle;

Reborn::Handler postprocessFramebufferHandler = Reborn::InvalidHandle;
Reborn::TextureDescriptor postprocessTextureDescriptor;
Reborn::Handler postprocessTextureHandler = Reborn::InvalidHandle;

Reborn::Handler postprocessProgrammHandler = Reborn::InvalidHandle;

Reborn::Handler screenQuadVAOHandler = Reborn::InvalidHandle;


Reborn::Renderer::Renderer(Window& window, const Vector2& _sceneFraimbufferSize):
	_context(window.createGLContext()),
	_window(window),
	sceneFraimbufferSize(_sceneFraimbufferSize),
	_camera(Reborn::toRadians(60), 1, 100, 1)
{
	initImGui(&window.getSDLWindow());
	renderBackend = new RenderBackend_GL(_context);
	auto& cbuffer = renderBackend->commandBuffer();
	renderBackend->commandBuffer().write(CommandBuffer::CommandType::INIT_BACKEND);
	//TEST ZONE
	struct ScreenQuadVertex
	{
		Vector3 pos;
		Vector2 uv;
	};
	ScreenQuadVertex vertices3[] = {
		{ Vector3(-1,-1, 0), Vector2( 0, 0) },
		{ Vector3( 1,-1, 0), Vector2( 1, 0) },
		{ Vector3( 1, 1, 0), Vector2( 1, 1) },
		{ Vector3(-1, 1, 0), Vector2( 0, 1) }
	};
	uint32_t indices2[] = { 0, 1, 2, 0, 2, 3 };

	Handler vbo = createVertexBuffer(vertices3, sizeof(ScreenQuadVertex) * 4);
	Handler ebo = createIndexBuffer(indices2, sizeof(uint32_t) * 6);
	
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

	//TEST ZONE END
	renderBackend->processComandBuffer();


	/*GLTexture colorAttachmentTexture;
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
	}*/

	//GLTexture postprocessTexture;
	//postprocessTexture.width = sceneFraimbufferSize.x;
	//postprocessTexture.height = sceneFraimbufferSize.y;
	//postprocessTexture.textureType = GL_TEXTURE_2D;
	//postprocessTexture.internalFromat = GL_RGB;
	//postprocessTexture.texelFormat = GL_RGB;
	//postprocessTexture.texelType = GL_UNSIGNED_BYTE;
	//postprocessTexture.addParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//postprocessTexture.addParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//postprocessTexture.addParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//postprocessTexture.addParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//postprocessFramebuffer.useAttachment(FramebufferAttachmentType::colorAttachment0, postprocessTexture);

	//create(postprocessFramebuffer);
	//if (!isFramebufferComplete(postprocessFramebuffer)) {
	//	LOG_ERROR << "postprocess framebuffer is not complete";
	//}

#if 0 //test stuff
	sceneFraimbuffer.colorAttachment0.value.texture.id = gl_Textures[colorAttachmentHandler];
	sceneFraimbuffer.colorAttachment1.value.texture.id = gl_Textures[outlinedGeomAttachmentHandler];
	sceneFraimbuffer.depthStensilAttachment.value.texture.id = gl_Renderbuffers[depthStensilHandler];
	sceneFraimbuffer.id = gl_Framebuffers[framebufferHandler];
#endif

	//bindMainFramebuffer();

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
#else
	//screenQuadVAO = VertexArrayObject();
	//screenQuadVAO.vbo.id = gl_vertexBuffers[vbo];
	//screenQuadVAO.ebo.id = gl_indexBuffers[ebo];
	//screenQuadVAO.ebo.size = 6;
	//screenQuadVAO.id = gl_vertexArrayObjects[vao]; 

#endif

	//postprocessPropgram = GLSLProgram(postprocessVertex, postprocessFragment);
	//create(postprocessPropgram);
//#if 0
//	postprocessPropgram.id = gl_ShaderPrograms[postprocessProgrammHandler];
//#endif
}

void Reborn::Renderer::beginFrame()
{
	
	//bind(sceneFraimbuffer);
	bindFramebuffer(framebufferHandler);
	setViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	//glViewport(0, 0, sceneFraimbufferSize.x, sceneFraimbufferSize.y);
	Vector4 clearColor0( 0.2, 1, 0.2, 1);
	//glClearBufferfv(GL_COLOR, 0, clearColor0.d);
	Vector4 clearColor1( 1, 0, 0, 1 );
	//glClearBufferfv(GL_COLOR, 1, clearColor1.d);
	//glClear(GL_DEPTH_BUFFER_BIT);

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
	//drawVAO(screenQuadVAO);
	
	//bindMainFramebuffer();
	setViewport(0,0,_window.width(), _window.height());
	//glViewport(0, 0, _window.width(), _window.height());
	//clear(FramebufferAttachmentType::colorAttachment0, true, false, this->clearColor);
	renderBackend->processComandBuffer();
	//glClear(GL_COLOR_BUFFER_BIT);

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
			.write(vertexSource.length())
			.write(vertexSource.data(), vertexSource.length())
			.write(fragmentSource.length())
			.write(fragmentSource.data(), fragmentSource.length());
	}
	return shaderProgramHandler;
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

void Reborn::Renderer::renderVAO(Handler vaoHandler, uint32_t size, uint32_t offset) {
	if (vaoHandler != Reborn::InvalidHandle) {
		renderBackend->commandBuffer()
			.write(Reborn::CommandBuffer::CommandType::RENDER_VAO)
			.write(vaoHandler)
			.write(size)
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

void Reborn::Renderer::create(BufferObject& buf) {
	glGenBuffers(1, &(buf.id));
}

void Reborn::Renderer::create(Framebuffer& fbo) {
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
	//return postprocessFramebuffer.colorAttachment0.value.texture;
	static GLTexture res = GLTexture();
	res.width = postprocessTextureDescriptor.width;
	res.height = postprocessTextureDescriptor.height;
	res.id = gl_Textures[postprocessTextureHandler];
	return res;
}

void Reborn::Renderer::setClearColor(const Vector3& _clearColor)
{
	this->clearColor = Vector4(_clearColor.xyz, 1);
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//bind(sceneFraimbuffer);
	//bindFramebuffer(framebufferHandler);
	//renderBackend->processComandBuffer();
	//GLfloat clearColor[] = { color.r, color.g, color.b, 1.0f };
	//glClearBufferfv(GL_COLOR, 0, clearColor);
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

	//sceneFraimbuffer.colorAttachment0.value.texture.width = newSize.x;
	//sceneFraimbuffer.colorAttachment0.value.texture.height = newSize.y;
	//bind(sceneFraimbuffer.colorAttachment0.value.texture);
	//upload(sceneFraimbuffer.colorAttachment0.value.texture, nullptr);

	//sceneFraimbuffer.colorAttachment1.value.texture.width = newSize.x;
	//sceneFraimbuffer.colorAttachment1.value.texture.height = newSize.y;
	//bind(sceneFraimbuffer.colorAttachment1.value.texture);
	//upload(sceneFraimbuffer.colorAttachment1.value.texture, nullptr);

	//sceneFraimbuffer.depthStensilAttachment.value.renderbuffer.width = newSize.x;
	//sceneFraimbuffer.depthStensilAttachment.value.renderbuffer.height = newSize.y;
	//bind(sceneFraimbuffer.depthStensilAttachment.value.renderbuffer);
	//upload(sceneFraimbuffer.depthStensilAttachment.value.renderbuffer);

	//postprocessFramebuffer.colorAttachment0.value.texture.width = newSize.x;
	//postprocessFramebuffer.colorAttachment0.value.texture.height = newSize.y;
	//bind(postprocessFramebuffer.colorAttachment0.value.texture);
	//upload(postprocessFramebuffer.colorAttachment0.value.texture, nullptr);
}

Reborn::Renderer::~Renderer()
{
	delete renderBackend;
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
		LOG_ERROR << "Reborn::Renderer::create invalid attachment type " << (int)fboAttachment.type;
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
		setFramebufferTexture(fbo, fboAttachment.value.texture, toGLType(fboAttachment.attachment));
	}
	else if (fboAttachment.type == GL_RENDERBUFFER) {
		setFramebufferRenderbuffer(fbo, fboAttachment.value.renderbuffer, toGLType(fboAttachment.attachment));
	}
	else {
		LOG_ERROR << "Reborn::Renderer::attach invalid attachment type " << (int)fboAttachment.type;
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