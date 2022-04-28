#pragma once
#include <Platform.h>
#include <Graphics/Common/Renderbuffer.h>

namespace Reborn
{
	class GLRenderbuffer : public Renderbuffer
	{
	public:
		GLRenderbuffer(
			const Vector2& _size,
			EnumValue _internalFormat,
			UIntValue id
		) :
			Renderbuffer(_size, API_TYPE),
			internalFormat(_internalFormat),
			id(_id)
		{};

		EnumValue internalFormat;
		UIntValue id;
	};
}
