#include "Core.h"
#include <glad/glad.h>
#include "RenderBackend_GL.h"
#include "Graphics/HandleAllocator.h"

namespace Reborn {
	GLenum toGLType(AttributeType type) {
		GLenum result = 0;
		switch (type)
		{
		case Reborn::AttributeType::FLOAT:
			result = GL_FLOAT;
			break;
		case Reborn::AttributeType::COUNT:
		default:
			assert(0, "unknown type");
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
			assert(0, "unknown type");
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

	RenderBackend_GL::RenderBackend_GL(Window& window) :
		RenderBackend(BackendType::OPEN_GL) 
	{
		SDL_Window& sdlWindow = window.getSDLWindow();

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		context = SDL_GL_CreateContext(&window.getSDLWindow());

		if (!context) {
			LOG_ERROR << "Failed to create context. \n" << SDL_GetError();
			context = nullptr;
		}

		assert(context != nullptr, "Failed to create context.");
	}

	RenderBackend_GL::~RenderBackend_GL() {
		SDL_GL_DeleteContext(context);
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
				_commandBuffer
					.read(handler)
					.read(sizeInBytes)
					.read(data);

				createVertexBuffer(handler, sizeInBytes, data);
				break;
			}
			case CommandBuffer::CommandType::CREATE_INDEX_BUFFER: {
				Handler handler;
				std::size_t sizeInBytes;
				void* data;
				_commandBuffer
					.read(handler)
					.read(sizeInBytes)
					.read(data);

				createIndexBuffer(handler, sizeInBytes, data);
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

				createVertexArrayObject(
					vaoHandler,
					vboHandler,
					eboHandler,
					numAttributes,
					attributes
				);
				break;

			}
			case CommandBuffer::CommandType::CREATE_TEXTURE: {
				Handler textureHandler;
				TextureDescriptor descriptor;

				_commandBuffer
					.read(textureHandler)
					.read(descriptor);

				createTexture(textureHandler, descriptor);
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

				_commandBuffer.readString(vertexSource);
				_commandBuffer.readString(fragmentSource);

				createShaderProgram(
					shaderProgramHandler,
					vertexSource,
					fragmentSource
				);

				break;
			}
			case CommandBuffer::CommandType::DELETE_SHADER_PROGRAM: {
				Handler shaderPrograamHandler;
				_commandBuffer.read(shaderPrograamHandler);
				deleteShaderProgram(shaderPrograamHandler);
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
				
				allocateRenderbuffer(renderbufferHandler, descriptor);
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

		if (!gladLoadGL()) {
			LOG_ERROR << "RenderBackend_GL::init Failed to init glad";
		}


		auto glVersion = glGetString(GL_VERSION);
		auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

		LOG_INFO << "using OpenGL " << glVersion;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(glMessageCallback, 0);


	}
	
	void RenderBackend_GL::createVertexBuffer(Handler handler, std::size_t sizeInBytes, void* data) {
		auto usage = GL_STATIC_DRAW; // pass through command buffer

		glGenBuffers(1, &gl_vertexBuffers[handler]);
		glBindBuffer(GL_ARRAY_BUFFER, gl_vertexBuffers[handler]);
		glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, usage);
	}

	void RenderBackend_GL::createIndexBuffer(Handler handler, std::size_t sizeInBytes, void* data) {
		auto usage = GL_STATIC_DRAW; // pass through command buffer
		glGenBuffers(1, &gl_indexBuffers[handler]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_indexBuffers[handler]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, usage);
	}

	void RenderBackend_GL::createVertexArrayObject(
		Handler vaoHandler, 
		Handler vboHandler, 
		Handler eboHandler, 
		uint16_t numAttributes, 
		const std::vector<VertexLayout::VertexAttribute>& attributes
	) {
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
	}

	void RenderBackend_GL::createTexture(Handler handler, const TextureDescriptor& descriptor) {
		glGenTextures(1, &gl_Textures[handler]);
		GLenum GLType = toGLType(descriptor.type);
		glBindTexture(GLType, gl_Textures[handler]);
		glTexParameteri(GLType, GL_TEXTURE_MIN_FILTER, toGLType(descriptor.minFilter));
		glTexParameteri(GLType, GL_TEXTURE_MAG_FILTER, toGLType(descriptor.magFilter));
		glTexParameteri(GLType, GL_TEXTURE_WRAP_S, toGLType(descriptor.wrapS));
		glTexParameteri(GLType, GL_TEXTURE_WRAP_T, toGLType(descriptor.wrapT));
	}

	void RenderBackend_GL::createShaderProgram(
		Handler handler, 
		const std::string& vertexSource, 
		const std::string& fragmentSource
	) {
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
		gl_ShaderPrograms[handler] = shaderProgram;

	}

	void RenderBackend_GL::deleteShaderProgram(Handler handler) {
		GLuint& gl_shaderProgram = gl_ShaderPrograms[handler];
		glDeleteProgram(gl_shaderProgram);
		gl_shaderProgram = 0;
	}

	void RenderBackend_GL::allocateRenderbuffer(Handler handler, RenderbufferDescriptor descriptor) {
		glBindRenderbuffer(GL_RENDERBUFFER, gl_Renderbuffers[handler]);
		glRenderbufferStorage(
			GL_RENDERBUFFER,
			toGLType(descriptor.internalFormat),
			descriptor.width,
			descriptor.height
		);
	}
}