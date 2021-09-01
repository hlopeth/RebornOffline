#include "Core.h"
#include "MeshResource.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

Reborn::MeshResource::MeshResource(): AbstractResource(0x6fc4f895)
{
}

bool Reborn::MeshResource::tryLoad(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 0);

	if (!scene) {
		LOG_ERROR 
			<< "MeshResource::tryLoad failed to read file " << path << std::endl 
			<< importer.GetErrorString();
		return false;
	}


	return false;
}

bool Reborn::MeshResource::unload()
{
	return false;
}