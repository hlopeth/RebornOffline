#include "Core.h"
#include "VertexLayout.h"

namespace Reborn {

	VertexLayout& VertexLayout::addAttribute(
		Attribute attribute,
		uint16_t size,
		AttributeType type,
		bool normalaized
	) {
		assert(wasBuilt == false);
		VertexLayout::VertexAttribute attrib = VertexLayout::VertexAttribute();
		attrib.index = static_cast<uint16_t>(attribute);
		attrib.size = size;
		attrib.normalized = normalaized;
		attrib.offsetBytes = INVALID_ATTRIBUTE_OFFSET;
		attrib.strideBytes = INVELID_ATTRIBUTE_STRIDE;
		attributes.push_back(attrib);
		return *this;
	}

	void VertexLayout::build() {
		std::sort(
			attributes.begin(), 
			attributes.end(),
			[](const VertexLayout::VertexAttribute& a, const VertexLayout::VertexAttribute& b) {
				return a.index < b.index;
			}
		);

		uint16_t currentOffset = 0;
		uint16_t currentStride = 0;

		for (uint16_t i = 0; i < attributes.size(); i++) {
			VertexLayout::VertexAttribute& attrib = attributes[i];
			attrib.offsetBytes = currentOffset;
			currentOffset += attrib.size * getSize(attrib.type);
		}

		for (uint16_t i = 0; i < attributes.size(); i++) {
			VertexLayout::VertexAttribute& attrib = attributes[i];
			attrib.strideBytes = currentOffset;
		}

		wasBuilt = true;
	}
	std::vector<VertexLayout::VertexAttribute>& VertexLayout::getAttributes()
	{
		return attributes;
	}
	const std::vector<VertexLayout::VertexAttribute>& VertexLayout::getAttributes() const
	{
		return attributes;
	}
	uint16_t VertexLayout::getSize(AttributeType type)
	{
		uint16_t result = 0;
		switch (type)
		{
		case Reborn::AttributeType::FLOAT:
			result = sizeof(float);
			break;
		case Reborn::AttributeType::COUNT:
		default:
			assert("unexpected attribute type");
			break;
		}
		return result;
	}
}