#pragma once
#include <Math/Vector.h>
#include "VertexLayout.h"
#include "VertexFactory.h"

namespace Reborn {
	class VertexFactory;

	struct MeshVertexType {
		Reborn::Vector3 position;
		Reborn::Vector3 normal;
		Reborn::Vector2 UV1;
	};

	class Mesh {
	public: 
		

		Mesh() = default;
		Mesh(
			size_t _indexCount,
			const uint32_t* _indices,
			size_t _vertexCount,
			const MeshVertexType* _vertices
		);
		Mesh(
			size_t _indexCount,
			const uint32_t* _indices,
			VertexFactory& vertexFactory
		);
		MeshVertexType* vertices() const;
		uint32_t* indices() const;
		size_t vertexCount() const;
		size_t indexCount() const;
		const VertexLayout& getVertexLayout() const;
		void getVertexBuffer(void*& outBuffer, size_t& outSize) const;
		void getIndexBuffer(void*& outBuffer, size_t& outSize) const;
	private:

		size_t _vertexCount = 0;
		size_t _indexCount = 0;
		std::unique_ptr<MeshVertexType[]> _vertexData = nullptr;
		std::unique_ptr<uint32_t[]> _indexData = nullptr;
		VertexLayout _vertexLayout;

	};
}