#pragma once
#include "APIType.h"

namespace Reborn
{
	class GrahicsResource
	{
	public:
		GrahicsResource(APIType _apiType): apiType(_apiType) {};
		APIType apiType;
	};
}