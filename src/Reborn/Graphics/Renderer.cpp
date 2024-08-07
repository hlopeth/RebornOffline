#pragma once
#include "Core.h"
#include <glad/glad.h>
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
				glBindVertexArray(0);
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
			case CommandBuffer::CommandType::DELETE_SHADER_PROGRAM: {
				Handler shaderPrograamHandler;
				_commandBuffer.read(shaderPrograamHandler);

				GLuint& gl_shaderProgram = gl_ShaderPrograms[shaderPrograamHandler];
				glDeleteProgram(gl_shaderProgram);
				gl_shaderProgram = 0;
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

				assert(shaderProgramHandler != InvalidHandle);

				GLuint gl_ShaderProgram = gl_ShaderPrograms[shaderProgramHandler];
				glUseProgram(gl_ShaderProgram);
				GLuint location = glGetUniformLocation(gl_ShaderProgram, paramName.c_str());

				switch (paramType)
				{
				case Reborn::UniformValueType::INT: {
					int value;
					_commandBuffer.read(value);
					glUniform1i(location, value);
					break;
				}
				case Reborn::UniformValueType::FLOAT: {
					float value;
					_commandBuffer.read(value);
					glUniform1f(location, value);
					break;
				}
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
				case Reborn::UniformValueType::VECTOR4F: {
					Vector4 value;
					_commandBuffer.read(value);
					glUniform4f(location, value.x, value.y, value.z, value.w);
					break;
				}
				case Reborn::UniformValueType::MATRIX2F: {
					Matrix2 value;
					bool transpose;
					_commandBuffer.read(value);
					_commandBuffer.read(transpose);
					glUniformMatrix2fv(location, 1, transpose, value._d);
					break;
				}
				case Reborn::UniformValueType::MATRIX3F: {
					Matrix3 value;
					bool transpose;
					_commandBuffer.read(value);
					_commandBuffer.read(transpose);
					glUniformMatrix3fv(location, 1, transpose, value._d);
					break;
				}
				case Reborn::UniformValueType::MATRIX4F: {
					Matrix4 value;
					bool transpose;
					_commandBuffer.read(value);
					_commandBuffer.read(transpose);
					glUniformMatrix4fv(location, 1, transpose, value._d);
					break;
				}
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
				uint32_t count;
				uint32_t offset;

				_commandBuffer
					.read(vaoHandler)
					.read(count)
					.read(offset);


				glBindVertexArray(gl_vertexArrayObjects[vaoHandler]);
				glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)offset);
				glBindVertexArray(0);
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
			.write(vertexSource.length())
			.write(vertexSource.data(), vertexSource.length())
			.write(fragmentSource.length())
			.write(fragmentSource.data(), fragmentSource.length());
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
	glDeleteProgram(program.id);
	program.id = -1;
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
	delete renderBackend;
#if REBORN_RENDER_BACKEND_OPENGL
	ImGui_ImplOpenGL3_Shutdown();
#else 
	static_assert(0, "no render backend???");
#endif
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
#if REBORN_RENDER_BACKEND_OPENGL
	ImGui_ImplSDL2_InitForOpenGL(window, _context);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
#else 
	static_assert(0, "no render backend???");
#endif
	return true;
}