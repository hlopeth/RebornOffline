#pragma once
#include "GraphicsResource.h"
#include <Math/Vector2.h>

namespace Reborn
{
	class TextureHandler: GrahicsResource
	{
	public:
		TextureHandler(
			const Vector2& _size,
			APIType apiType
		) : GrahicsResource(apiType), size(_size) {};

		const Vector2& getSize() const
		{
			return size;
		}

	protected:
		Vector2 size;
	};
}