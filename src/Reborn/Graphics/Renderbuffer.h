#pragma once
#include "Platform.h"

namespace Reborn {
	struct Renderbuffer {
		SizeiValue width;
		SizeiValue height;
		EnumValue internalFormat;
		UIntValue id;
	};
}