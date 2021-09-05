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
    createVAO();
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
{
    LOG_DEBUG << "copy constructor";
    createVAO();
}

Reborn::Mesh::Mesh(Mesh && mesh):
    _vertexData(std::move(mesh._vertexData)),
    _indexData(std::move(mesh._indexData)),
    _indexCount(mesh._indexCount),
    _vertexCount(mesh._vertexCount),
    _hasIndeces(mesh._hasIndeces),
    _hasPositions(mesh._hasPositions),
    _hasNormals(mesh._hasNormals),
    _hasUV1(mesh._hasUV1)
{
    mesh._indexCount = 0;
    mesh._hasIndeces = false;
    mesh._vertexCount = 0;
    mesh._hasPositions = false;
    mesh._hasNormals= false;
    mesh._hasUV1 = false;
    LOG_DEBUG << "move constructor";

    createVAO();
}

Reborn::Mesh& Reborn::Mesh::operator=(const Mesh & mesh)
{
    _indexCount = mesh.indexCount();
    _vertexCount = mesh.vertexCount();

    _indexData = std::make_unique<uint32_t[]>(_indexCount);
    _hasIndeces = true;
    memcpy(_indexData.get(), mesh.indices(), sizeof(uint32_t) * _indexCount);

    _hasPositions = mesh.positions() != nullptr;
    _hasNormals = mesh.normals() != nullptr;
    _hasUV1 = mesh.UV1() != nullptr;

    int vertexSize = _hasPositions * 3 + _hasNormals * 3 + _hasUV1 * 2;
    _vertexData = std::make_unique<float[]>(vertexSize * _vertexCount);

    memcpy(_vertexData.get() + positionsOffset(), mesh.positions(), sizeof(Vector3) * _vertexCount);

    if (mesh.normals() != nullptr) {
        memcpy(_vertexData.get() + normalsOffset(), mesh.normals(), sizeof(Vector3) * _vertexCount);
    }
    if (mesh.UV1() != nullptr) {
        memcpy(_vertexData.get() + uv1Offset(), mesh.UV1(), sizeof(Vector2) * _vertexCount);
    }
    createVAO();
    return *this;
}

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

const Reborn::VertexArrayObject& Reborn::Mesh::getVAO() const
{
    return _vao;
}

Reborn::VertexArrayObject& Reborn::Mesh::getVAO()
{
    return _vao;
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

void Reborn::Mesh::createVAO()
{
    int vertexSize = _hasPositions * 3 + _hasNormals * 3 + _hasUV1 * 2;
    Reborn::VertexBufferObject vbo(_vertexData.get(), _vertexCount * vertexSize);
    Reborn::ElementBufferObject ebo(_indexData.get(), _indexCount);
    std::vector<VertexAttribute> attributes;

    if (_hasPositions) {
        attributes.push_back(positionVertexAttribute(false, 0, positionsOffset()));
    }
    if (_hasNormals) {
        attributes.push_back(normalVertexAttribute(false, 0, normalsOffset()));
    }
    if (_hasUV1) {
        attributes.push_back(uv1VertexAttribute(false, 0, uv1Offset()));
    }    
    _vao = VertexArrayObject(vbo, ebo, attributes);
}
