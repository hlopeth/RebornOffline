#include "Core.h"
#include "ModelResource.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Reborn::ModelResource::ModelResource(): AbstractResource(0x6fc4f895)
{
}

bool Reborn::ModelResource::tryLoad(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene) {
		LOG_ERROR 
			<< "MeshResource::tryLoad failed to read file " << path << std::endl 
			<< importer.GetErrorString();
		return false;
	}

	if (scene->HasMeshes()) {
		aiMesh* firstMesh = scene->mMeshes[0];

		size_t numIndices = firstMesh->mNumFaces * 3;
		uint32_t* indices = new uint32_t[numIndices];
		for (int i = 0; i < firstMesh->mNumFaces; i++) {
			aiFace face = firstMesh->mFaces[i];
			indices[3 * i + 0] = face.mIndices[0];
			indices[3 * i + 1] = face.mIndices[1];
			indices[3 * i + 2] = face.mIndices[2];
		}

		Vector3* positions = new Vector3[firstMesh->mNumVertices];
		for (int i = 0; i < firstMesh->mNumVertices; i++) {
			aiVector3D v = firstMesh->mVertices[i];
			positions[i] = Vector3(v.x, v.y, v.z);
		}

		Vector3* normals = nullptr;
		if (firstMesh->HasNormals()) {
			normals = new Vector3[firstMesh->mNumVertices];
			for (int i = 0; i < firstMesh->mNumVertices; i++) {
				aiVector3D n = firstMesh->mNormals[i];
				normals[i] = Vector3(n.x, n.y, n.z);
			}
		}

		mesh = Mesh(numIndices, indices, firstMesh->mNumVertices, positions, normals);
		return true;
	}
	return false;
}

bool Reborn::ModelResource::unload()
{
	return true;
}

const Reborn::Mesh& Reborn::ModelResource::getMesh() const
{
	return mesh;
}
