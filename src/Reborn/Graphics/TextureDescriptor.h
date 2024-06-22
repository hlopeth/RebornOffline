#pragma once

namespace Reborn {
	enum class TextureType {
		TEXTURE_2D,
		COUNT
	};

	enum class TextureFormat {
		RGB,
		RGBA,
		COUNT
	};

	enum class PixelFormat {
		RGB,
		RGBA,
		COUNT
	};

	enum class TexelType {
		UNSIGNED_BYTE,
		COUNT
	};

	enum class TextureFilter {
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		LINEAR_MIPMAP_LINEAR,
		COUNT
	};

	enum class TextureWrapping {
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		MIRRORED_REPEAT,
		REPEAT,
		MIRROR_CLAMP_TO_EDGE,
		COUNT
	};

	struct TextureDescriptor {
		uint32_t width = 0;
		uint32_t height = 0;
		TextureType type;
		TextureFormat internalFormat;
		PixelFormat pixelFormat; //I know that is texel, but I use pixel to differentiate names
		TexelType texelType;
		TextureFilter minFilter = TextureFilter::NEAREST;
		TextureFilter magFilter = TextureFilter::NEAREST;
		TextureWrapping wrapS = TextureWrapping::CLAMP_TO_EDGE;
		TextureWrapping wrapT = TextureWrapping::CLAMP_TO_EDGE;
	};
}