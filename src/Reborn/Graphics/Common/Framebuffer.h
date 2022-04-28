#pragma once
#include "GraphicsResource.h"

namespace Reborn
{
	class Framebuffer : public GrahicsResource
	{
	public:
		Framebuffer(APIType apiType): GrahicsResource(apiType) {}
	};
}