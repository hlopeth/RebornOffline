#include "Core.h"
#include "Mesh.h"

Reborn::Mesh::Mesh(
    const size_t indexCount,
    const uint32_t* _indices,
    const size_t vertexCount,
    const Vector3* _positions,
    const Vector3* _normals, 
    const Vector2* _UV1 
)
{
    _indexCount = indexCount;
    _vertexCount = vertexCount;

    _indexData = std::make_unique<uint32_t[]>(_indexCount);
    _hasIndeces = true;
    memcpy(_indexData.get(), _indices, sizeof(uint32_t) * _indexCount);

    _hasPositions = _positions != nullptr;
    _hasNormals = _normals != nullptr;
    _hasUV1 = _UV1 != nullptr;

    int vertexSize = _hasPositions * 3 + _hasNormals * 3 + _hasUV1 * 2;
    _vertexData = std::make_unique<float[]>(vertexSize * _vertexCount);

    memcpy(_vertexData.get() + positionsOffset(), _positions, sizeof(Vector3) * _vertexCount);

    if (_normals != nullptr) {
        memcpy(_vertexData.get() + normalsOffset(), _normals, sizeof(Vector3) * _vertexCount);
    }
    if (_UV1 != nullptr) {
        memcpy(_vertexData.get() + uv1Offset(), _UV1, sizeof(Vector2) * _vertexCount);
    }
}

Reborn::Mesh::Mesh(const Mesh& mesh):
    Mesh(
        mesh.indexCount(),
        mesh.indices(),
        mesh.vertexCount(),
        mesh.positions(),
        mesh.normals(),
        mesh.UV1()
    )
{}

bool Reborn::Mesh::hasPositions() const
{
    return _hasPositions;
}

bool Reborn::Mesh::hasNormals() const
{
    return _hasNormals;
}

bool Reborn::Mesh::hasUV1() const
{
    return _hasUV1;
}

bool Reborn::Mesh::hasIndices() const
{
    return _hasIndeces;
}

Reborn::VertexArrayObject Reborn::Mesh::getVAO() const
{
    int vertexSize = _hasPositions * 3 + _hasNormals * 3 + _hasUV1 * 2;
    Reborn::VertexBufferObject vbo(_vertexData.get(), _vertexCount * vertexSize);
    std::vector<VertexAttribute> attributes{
        positionVertexAttribute(false, 0, positionsOffset()),
        normalVertexAttribute(false, 0, normalsOffset()),
        uv1VertexAttribute(false, 0, uv1Offset())
    };
    return VertexArrayObject(vbo, attributes);
}

Reborn::Vector3* Reborn::Mesh::positions() const
{
    if (hasPositions()) {
        return reinterpret_cast<Vector3*>(_vertexData.get() + positionsOffset());
    }
    else {
        return nullptr;
    }
}

Reborn::Vector3* Reborn::Mesh::normals() const
{
    if (hasNormals()) {
        return reinterpret_cast<Vector3*>(_vertexData.get() + normalsOffset());
    }
    else {
        return nullptr;
    }
}

Reborn::Vector2* Reborn::Mesh::UV1() const
{
    if (hasUV1()) {
        return reinterpret_cast<Vector2*>(_vertexData.get() + uv1Offset());
    }
    else {
        return nullptr;
    }
}

uint32_t* Reborn::Mesh::indices() const
{
    if (hasIndices()) {
        return _indexData.get();
    }
    else {
        return nullptr;
    }
}

size_t Reborn::Mesh::vertexCount() const
{
    return _vertexCount;
}

size_t Reborn::Mesh::indexCount() const
{
    return _indexCount;
}

int Reborn::Mesh::positionsOffset() const
{
    return 0;
}

int Reborn::Mesh::normalsOffset() const
{
    return _hasPositions * 3 * _vertexCount;
}

int Reborn::Mesh::uv1Offset() const
{
    return (_hasPositions * 3 + _hasNormals * 3) * _vertexCount;
}
