#include "Core.h"
#include "Mesh.h"

Reborn::Mesh::Mesh(
    size_t inIndexCount, 
    const uint32_t* inIndices, 
    size_t inVertexCount, 
    const MeshVertexType* inVertices)
{
    _indexCount = inIndexCount;
    _vertexCount = inVertexCount;

    _indexData = std::make_unique<uint32_t[]>(_indexCount);
    memcpy(_indexData.get(), inIndices, sizeof(uint32_t) * _indexCount);


    _vertexData = std::make_unique<MeshVertexType[]>(sizeof(MeshVertexType) * _vertexCount);
    memcpy(_vertexData.get(), inVertices, sizeof(MeshVertexType) * _vertexCount);


    _vertexLayout
        .addAttribute(Attribute::POSITION, 3, AttributeType::FLOAT)
        .addAttribute(Attribute::NORMAL, 3, AttributeType::FLOAT)
        .addAttribute(Attribute::UV1, 2, AttributeType::FLOAT)
        .build();
}

Reborn::Mesh::Mesh(size_t inIndexCount, const uint32_t* inIndices, VertexFactory& vertexFactory)
{
    _indexCount = inIndexCount;

    _indexData = std::make_unique<uint32_t[]>(_indexCount);
    memcpy(_indexData.get(), inIndices, sizeof(uint32_t) * _indexCount);

    MeshVertexType* vd;
    vertexFactory.build(_vertexCount, vd);
    _vertexData = std::unique_ptr<MeshVertexType[]>(vd);

    _vertexLayout
        .addAttribute(Attribute::POSITION, 3, AttributeType::FLOAT)
        .addAttribute(Attribute::NORMAL, 3, AttributeType::FLOAT)
        .addAttribute(Attribute::UV1, 2, AttributeType::FLOAT)
        .build();
}

Reborn::MeshVertexType* Reborn::Mesh::vertices() const
{
    return _vertexData.get();
}

uint32_t* Reborn::Mesh::indices() const
{
    return _indexData.get();
}

size_t Reborn::Mesh::vertexCount() const
{
    return _vertexCount;
}

size_t Reborn::Mesh::indexCount() const
{
    return _indexCount;
}

const Reborn::VertexLayout& Reborn::Mesh::getVertexLayout() const
{
    return _vertexLayout;
}

void Reborn::Mesh::getVertexBuffer(void* &outBuffer, size_t &outSize) const
{
    outSize = _vertexCount * sizeof(MeshVertexType);
    outBuffer = _vertexData.get();
}

void Reborn::Mesh::getIndexBuffer(void*& outBuffer, size_t& outSize) const
{
    outSize = sizeof(uint32_t) * _indexCount;
    outBuffer = _indexData.get();
}
