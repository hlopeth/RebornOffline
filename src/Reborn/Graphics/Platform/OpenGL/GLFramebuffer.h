#pragma once
#include <Platform.h>
#include <Graphics/Common/Framebuffer.h>
#include "GLRenderbuffer.h"
#include "GLTextureHandler.h"

namespace Reborn 
{
	enum GLFramebufferAttachmentType 
	{
		colorAttachment0 = REBORN_COLOR_ATTACHMENT0,
		colorAttachment1 = REBORN_COLOR_ATTACHMENT1,
		colorAttachment2 = REBORN_COLOR_ATTACHMENT2,
		depthStensilAttachment = REBORN_DEPTH_STENCIL_ATTACHMENT,
		emptyAttachment = 0
	};

	union GLFramebufferAttachmentTarget 
	{
		GLTextureHandler texture;
		GLRenderbuffer renderbuffer;
	};

	struct GLFramebufferAttachment 
	{
		EnumValue targetType = 0; //GL_TEXTURE_2D or GL_RENDERBUFFER
		GLFramebufferAttachmentType attachment = GLFramebufferAttachmentType::emptyAttachment; //GL_COLOR_ATTACHMENTX or GL_DEPTH_STENCIL_ATTACHMENT or GL_EMPLTY_ATTACHMENT
		GLFramebufferAttachmentTarget target;
	};


	class GLFramebuffer : public Framebuffer
	{
	public:
		GLFramebuffer() : Framebuffer(API_TYPE) {};

		void useAttachment(GLFramebufferAttachmentType attachment, GLTextureHandler texture) 
		{
			GLFramebufferAttachmentTarget value{};
			value.texture = texture;
			useAttachment(attachment, value, REBORN_TEXTURE_2D);
		};

		void useAttachment(GLFramebufferAttachmentType attachment, GLRenderbuffer renderbuffer) 
		{
			GLFramebufferAttachmentTarget value{};
			value.renderbuffer = renderbuffer;
			useAttachment(attachment, value, REBORN_RENDERBUFFER);
		};

		void useAttachment(
			GLFramebufferAttachmentType attachment,
			GLFramebufferAttachmentTarget value, 
			EnumValue type
		) 
		{
			GLFramebufferAttachment* initializedAttachment = nullptr;
			switch (attachment)
			{
			case GLFramebufferAttachmentType::colorAttachment0:
				initializedAttachment = &colorAttachment0;
				initializedAttachment->attachment = GLFramebufferAttachmentType::colorAttachment0;
				break;
			case GLFramebufferAttachmentType::colorAttachment1:
				initializedAttachment = &colorAttachment1;
				initializedAttachment->attachment = GLFramebufferAttachmentType::colorAttachment1;
				break;
			case GLFramebufferAttachmentType::colorAttachment2:
				initializedAttachment = &colorAttachment2;
				initializedAttachment->attachment = GLFramebufferAttachmentType::colorAttachment2;
				break;
			case GLFramebufferAttachmentType::depthStensilAttachment:
				initializedAttachment = &depthStensilAttachment;
				initializedAttachment->attachment = GLFramebufferAttachmentType::depthStensilAttachment;
				break;
			default:
				LOG_ERROR << "Framebuffer::useAttachment uncnown attachment type " << attachment;
				break;
			}

			initializedAttachment->targetType= type;
			if (type == GL_RENDERBUFFER) {
				initializedAttachment->target.renderbuffer = value.renderbuffer;
			}
			else if(type == GL_TEXTURE_2D) {
				initializedAttachment->target.texture = value.texture;
			}
			else {
				LOG_ERROR << "Framebuffer::useAttachment uncnown target type " << attachment;
			}
		};

		GLFramebufferAttachment colorAttachment0{};
		GLFramebufferAttachment colorAttachment1{};
		GLFramebufferAttachment colorAttachment2{};
		GLFramebufferAttachment depthStensilAttachment{};
		UIntValue id;
	};
}