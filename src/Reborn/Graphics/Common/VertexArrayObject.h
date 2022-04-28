#pragma once
#include "GraphicsResource.h"

namespace Reborn
{
	class VertexArrayObject : public GrahicsResource
	{
	public:
		VertexArrayObject(APIType apiType) : GrahicsResource(apiType) {};
	};
}