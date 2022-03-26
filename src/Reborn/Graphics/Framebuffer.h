#pragma once
#include "Renderbuffer.h"
#include "TextureHandler.h"

namespace Reborn {
	enum FramebufferAttachmentType {
		colorAttachment0 = REBORN_COLOR_ATTACHMENT0,
		colorAttachment1 = REBORN_COLOR_ATTACHMENT1,
		colorAttachment2 = REBORN_COLOR_ATTACHMENT2,
		depthStensilAttachment = REBORN_DEPTH_STENCIL_ATTACHMENT,
		emptyAttachment = 0
	};

	union FramebufferAttachmentValue {
		TextureHandler texture;
		Renderbuffer renderbuffer;
		FramebufferAttachmentValue() { memset(this, 0, sizeof(FramebufferAttachmentValue)); }
	};

	struct FramebufferAttachment {

		EnumValue type = 0; //GL_TEXTURE_2D or GL_RENDERBUFFER
		FramebufferAttachmentType attachment = FramebufferAttachmentType::emptyAttachment; //GL_COLOR_ATTACHMENTX or GL_DEPTH_STENCIL_ATTACHMENT or GL_EMPLTY_ATTACHMENT
		FramebufferAttachmentValue value;
	};
		

	struct Framebuffer {
		FramebufferAttachment colorAttachment0;
		FramebufferAttachment colorAttachment1;
		FramebufferAttachment colorAttachment2;
		FramebufferAttachment depthStensilAttachment;
		UIntValue id;

		void useAttachment(FramebufferAttachmentType attachment, TextureHandler texture) {
			FramebufferAttachmentValue value;
			value.texture = texture;
			useAttachment(attachment, value, REBORN_TEXTURE_2D);
		};
		void useAttachment(FramebufferAttachmentType attachment, Renderbuffer renderbuffer) {
			FramebufferAttachmentValue value;
			value.renderbuffer = renderbuffer;
			useAttachment(attachment, value, REBORN_RENDERBUFFER);
		};
		void useAttachment(FramebufferAttachmentType attachment, FramebufferAttachmentValue value, EnumValue type) {
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
				LOG_ERROR << "Framebuffer::useAttachment uncnown attachment type " << attachment;
				break;
			}

			initializedAttachment->type = type;
			initializedAttachment->value = value;
		};

	};
}