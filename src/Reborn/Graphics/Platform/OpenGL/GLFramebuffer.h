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

	union GLFramebufferAttachmentValue 
	{
		TextureHandler texture;
		Renderbuffer renderbuffer;
		GLFramebufferAttachmentValue() 
		{ 
			memset(this, 0, sizeof(GLFramebufferAttachmentValue)); 
		}
	};

	struct GLFramebufferAttachment 
	{

		EnumValue type = 0; //GL_TEXTURE_2D or GL_RENDERBUFFER
		GLFramebufferAttachmentType attachment = GLFramebufferAttachmentType::emptyAttachment; //GL_COLOR_ATTACHMENTX or GL_DEPTH_STENCIL_ATTACHMENT or GL_EMPLTY_ATTACHMENT
		GLFramebufferAttachmentValue value;
	};


	class GLFramebuffer : public Framebuffer
	{
	public:
		GLFramebuffer() : Framebuffer(API_TYPE) {};

		void useAttachment(GLFramebufferAttachmentType attachment, GLTextureHandler texture) 
		{
			GLFramebufferAttachmentValue value;
			value.texture = texture;
			useAttachment(attachment, value, REBORN_TEXTURE_2D);
		};

		void useAttachment(GLFramebufferAttachmentType attachment, GLRenderbuffer renderbuffer) 
		{
			GLFramebufferAttachmentValue value;
			value.renderbuffer = renderbuffer;
			useAttachment(attachment, value, REBORN_RENDERBUFFER);
		};

		void useAttachment(
			GLFramebufferAttachmentType attachment,
			GLFramebufferAttachmentValue value, 
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

			initializedAttachment->type = type;
			initializedAttachment->value = value;
		};

		GLFramebufferAttachment colorAttachment0;
		GLFramebufferAttachment colorAttachment1;
		GLFramebufferAttachment colorAttachment2;
		GLFramebufferAttachment depthStensilAttachment;
		UIntValue id;
	};
}