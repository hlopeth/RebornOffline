#pragma once
#include "Mesh.h"

namespace Reborn {
	struct MeshVertexType;

	class VertexFactory {
	public:
		virtual void build(size_t& outNumVertices, MeshVertexType*& outVertices) = 0;
	};


	/*
	* Usage example
	* DefaultVertexFactory vf = DefaultVertexFactory().setSize(n).setPositions(inPositions).setNormals(inNormals);
	*/
	class DefaultVertexFactory : public VertexFactory {
	public:
		DefaultVertexFactory() = default;
		~DefaultVertexFactory();

		DefaultVertexFactory& setSize(const size_t numVertices);
		DefaultVertexFactory& setPositions(const Vector3* positons);
		DefaultVertexFactory& setPositions(const float* positions);
		DefaultVertexFactory& setNormals(const Vector3* normals);
		DefaultVertexFactory& setNormals(const float* normals);
		DefaultVertexFactory& setUV1(const Vector2* uv);
		DefaultVertexFactory& setUV1(const float* uv);


		virtual void build(size_t& outNumVertices, MeshVertexType*& outVertices) override;
	private:
		size_t numVertices;
		MeshVertexType* vertices = nullptr;
	};
}