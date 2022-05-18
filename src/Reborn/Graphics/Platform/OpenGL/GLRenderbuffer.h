#pragma once
#include <Platform.h>
#include <Graphics/Common/Renderbuffer.h>

namespace Reborn
{
	class GLRenderbuffer : public Renderbuffer
	{
	public:
		GLRenderbuffer():
			Renderbuffer(Vector2(0), API_TYPE),
			internalFormat(0),
			id(0) {}
		GLRenderbuffer(
			const Vector2& _size,
			EnumValue _internalFormat,
			UIntValue _id
		) :
			Renderbuffer(_size, API_TYPE),
			internalFormat(_internalFormat),
			id(_id)
		{};

		EnumValue internalFormat;
		UIntValue id;
	};
}
