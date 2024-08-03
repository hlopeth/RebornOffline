#include "Core.h"
#include "VertexFactory.h"

Reborn::DefaultVertexFactory::~DefaultVertexFactory()
{
    if (vertices != nullptr) {
        delete[] vertices;
    }
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setSize(const size_t _numVertices)
{
    this->numVertices = _numVertices;
    vertices = new Reborn::MeshVertexType[_numVertices];
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setPositions(const Vector3* positions)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].position = positions[i];
    }
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setPositions(const float* positions)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].position.x = positions[i * 3 + 0];
        vertices[i].position.y = positions[i * 3 + 1];
        vertices[i].position.z = positions[i * 3 + 2];
    }
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setNormals(const Vector3* normals)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].normal = normals[i];
    }
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setNormals(const float* normals)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].normal.x = normals[i * 3 + 0];
        vertices[i].normal.y = normals[i * 3 + 1];
        vertices[i].normal.z = normals[i * 3 + 2];
    }
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setUV1(const Vector2* uv)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].UV1 = uv[i];
    }
    return *this;
}

Reborn::DefaultVertexFactory& Reborn::DefaultVertexFactory::setUV1(const float* uv)
{
    assert(vertices == nullptr);
    for (uint32_t i = 0; i < numVertices; i++) {
        vertices[i].UV1.x = uv[i * 2 + 0];
        vertices[i].UV1.y = uv[i * 2 + 1];
    }
    return *this;
}

void Reborn::DefaultVertexFactory::build(size_t& outNumVertices, MeshVertexType*& outVertices)
{
    outNumVertices = numVertices;
    outVertices = vertices;
    vertices = nullptr;
}