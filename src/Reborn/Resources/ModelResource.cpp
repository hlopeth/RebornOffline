#include "Core.h"
#include "ModelResource.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

Reborn::ModelResource::ModelResource(): AbstractResource(0x6fc4f895)
{
}

bool Reborn::ModelResource::tryLoad(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 0);

	if (!scene) {
		LOG_ERROR 
			<< "MeshResource::tryLoad failed to read file " << path << std::endl 
			<< importer.GetErrorString();
		return false;
	}

	if (scene->HasMeshes()) {
		aiMesh* firstMesh = scene->mMeshes[0];
	}
	return false;
}

bool Reborn::ModelResource::unload()
{
	return false;
}