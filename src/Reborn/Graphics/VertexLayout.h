#pragma once

namespace Reborn {
	enum class Attribute {
		POSITION = 0,
		NORMAL = 1,
		UV1 = 2,
		COUNT
	};

	enum class AttributeType {
		FLOAT,
		COUNT
	};


	class VertexLayout {
	public:
		struct VertexAttribute {
			uint16_t index;
			uint16_t size;
			bool normalized;
			AttributeType type;
			uint16_t offsetBytes;
			uint16_t strideBytes;
		};

		VertexLayout() = default;
		VertexLayout& addAttribute(
			Attribute attribute,
			uint16_t size,
			AttributeType type,
			bool normalaized = false
		);
		void build();
		std::vector<VertexLayout::VertexAttribute>& getAttributes();
		const std::vector<VertexLayout::VertexAttribute>& getAttributes() const;
	private:
		uint16_t getSize(AttributeType type);

		static const uint16_t INVALID_ATTRIBUTE_OFFSET = UINT_LEAST16_MAX;
		static const uint16_t INVELID_ATTRIBUTE_STRIDE = UINT_LEAST16_MAX;

		bool wasBuilt = false;
		std::vector<VertexLayout::VertexAttribute> attributes;
	};
}