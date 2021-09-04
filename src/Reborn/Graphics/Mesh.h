#pragma once
#include <Math/Vector.h>
#include "VertexArrayObject.h"

namespace Reborn {
	class Mesh {
	public: 
		Mesh() = default;
		Mesh(
			size_t _indexCount,
			const uint32_t* _indices,
			size_t _vertexCount,
			const Vector3* _positions,
			const Vector3* _normals = nullptr,
			const Vector2* _UV1 = nullptr
			);
		Mesh(
			Mesh&& mesh
		);
		Mesh& operator=(const Mesh& mesh);
		bool hasPositions() const;
		bool hasNormals() const;
		bool hasUV1() const;
		bool hasIndices() const;
		VertexArrayObject getVAO() const;
		Vector3* positions() const;
		Vector3* normals() const;
		Vector2* UV1() const;
		uint32_t* indices() const;
		size_t vertexCount() const;
		size_t indexCount() const;
	public:
		//prevent copy
		Mesh(
			const Mesh& mesh
		);
	private:
		int positionsOffset() const;
		int normalsOffset() const;
		int uv1Offset() const;

		size_t _vertexCount = 0;
		size_t _indexCount = 0;
		bool _hasPositions = false;
		bool _hasNormals = false;
		bool _hasUV1 = false;
		bool _hasIndeces = false;
		std::unique_ptr<float[]> _vertexData = nullptr;
		std::unique_ptr<uint32_t[]> _indexData = nullptr;

	};
}