#pragma once
#include <SDL_opengl.h>
#include "GLTexture.h"
#include "Renderbuffer.h"

namespace Reborn {
	enum class FramebufferAttachmentType {
		colorAttachment0 = GL_COLOR_ATTACHMENT0,
		colorAttachment1 = GL_COLOR_ATTACHMENT1,
		colorAttachment2 = GL_COLOR_ATTACHMENT2,
		depthStensilAttachment = GL_DEPTH_STENCIL_ATTACHMENT,
		emptyAttachment = 0
	};

	union FramebufferAttachmentValue {
		GLTexture texture;
		Renderbuffer renderbuffer;
		FramebufferAttachmentValue() { memset(this, 0, sizeof(FramebufferAttachmentValue)); }
	};

	struct FramebufferAttachment {

		GLenum type = 0; //GL_TEXTURE_2D or GL_RENDERBUFFER
		FramebufferAttachmentType attachment = FramebufferAttachmentType::emptyAttachment; //GL_COLOR_ATTACHMENTX or GL_DEPTH_STENCIL_ATTACHMENT or GL_EMPLTY_ATTACHMENT
		FramebufferAttachmentValue value;
	};
		

	struct Framebuffer {
		FramebufferAttachment colorAttachment0;
		FramebufferAttachment colorAttachment1;
		FramebufferAttachment colorAttachment2;
		FramebufferAttachment depthStensilAttachment;
		GLuint id;

		void useAttachment(FramebufferAttachmentType attachment, GLTexture texture) {
			FramebufferAttachmentValue value;
			value.texture = texture;
			useAttachment(attachment, value, GL_TEXTURE_2D);
		};
		void useAttachment(FramebufferAttachmentType attachment, Renderbuffer renderbuffer) {
			FramebufferAttachmentValue value;
			value.renderbuffer = renderbuffer;
			useAttachment(attachment, value, GL_RENDERBUFFER);
		};
		void useAttachment(FramebufferAttachmentType attachment, FramebufferAttachmentValue value, GLenum type) {
			FramebufferAttachment* initializedAttachment = nullptr;
			switch (attachment)
			{
			case FramebufferAttachmentType::colorAttachment0:
				initializedAttachment = &colorAttachment0;
				initializedAttachment->attachment = FramebufferAttachmentType::colorAttachment0;
				break;
			case FramebufferAttachmentType::colorAttachment1:
				initializedAttachment = &colorAttachment1;
				initializedAttachment->attachment = FramebufferAttachmentType::colorAttachment1;
				break;
			case FramebufferAttachmentType::colorAttachment2:
				initializedAttachment = &colorAttachment2;
				initializedAttachment->attachment = FramebufferAttachmentType::colorAttachment2;
				break;
			case FramebufferAttachmentType::depthStensilAttachment:
				initializedAttachment = &depthStensilAttachment;
				initializedAttachment->attachment = FramebufferAttachmentType::depthStensilAttachment;
				break;
			default:
				LOG_ERROR << "Framebuffer::useAttachment uncnown attachment type " << (int)attachment;
				break;
			}

			initializedAttachment->type = type;
			initializedAttachment->value = value;
		};

	};
}