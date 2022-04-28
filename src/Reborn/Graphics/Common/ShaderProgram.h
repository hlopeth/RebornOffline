#pragma once
#include "GraphicsResource.h"

namespace Reborn
{
	class ShaderProgram: public GrahicsResource
	{
	public:
		ShaderProgram(APIType apiType): GrahicsResource(apiType) {};
	};
}