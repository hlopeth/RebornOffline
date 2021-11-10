#include "Core.h"
#include "ModelResource.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Core/Application.h>
#include <queue>


void loadMesh(Reborn::Model* model, const aiMesh* assimpMesh) {
	unsigned int numVertices = assimpMesh->mNumVertices;
	uint32_t numIndices = assimpMesh->mNumFaces * 3;

	uint32_t* indices = new uint32_t[numIndices];
	for (int i = 0; i < assimpMesh->mNumFaces; i++) {
		aiFace face = assimpMesh->mFaces[i];
		indices[3 * i + 0] = face.mIndices[0];
		indices[3 * i + 1] = face.mIndices[1];
		indices[3 * i + 2] = face.mIndices[2];
	}

	Reborn::Vector3* positions = new Reborn::Vector3[numVertices];
	for (int i = 0; i < numVertices; i++) {
		aiVector3D v = assimpMesh->mVertices[i];
		positions[i] = Reborn::Vector3(v.x, v.y, v.z);
	}

	Reborn::Vector3* normals = nullptr;
	if (assimpMesh->HasNormals()) {
		normals = new Reborn::Vector3[numVertices];
		for (int i = 0; i < numVertices; i++) {
			aiVector3D n = assimpMesh->mNormals[i];
			normals[i] = Reborn::Vector3(n.x, n.y, n.z);
		}
	}

	model->meshes.emplace_back(numIndices, indices, numVertices, positions, normals);
}

int loadTransform(
	Reborn::Model* model,
	const aiNode* node) {
	const aiMatrix4x4 tr = node->mTransformation;
	aiVector3D scaling, position;
	aiQuaternion rotation;
	tr.Decompose(
		scaling,
		rotation,
		position
	);
	Reborn::Vector3 rebornPosition = Reborn::Vector3(position.x, position.y, position.z);
	Reborn::Vector3 rebornScale = Reborn::Vector3(scaling.x, scaling.y, scaling.z);
	Reborn::Vector3 rebornRotation = Reborn::Vector3(0); //TODO loading rotation
	model->transforms.emplace_back(rebornPosition, rebornScale, rebornRotation);
	return model->transforms.size() - 1;
}

//возвращает индекс дочерней ноды
int loadChildNode(
	Reborn::Model* model,
	const aiScene* scene,
	const aiNode* currentNode,
	int parentNodeIndex) {
	Reborn::Model::Node rebornNode;
	if (currentNode->mNumMeshes > 0) {
		rebornNode.meshIndex = currentNode->mMeshes[0];
	}
	else {
		rebornNode.meshIndex = -1;
	}
	rebornNode.transformIndex = loadTransform(model, currentNode);
	rebornNode.parentIndex = parentNodeIndex;
	rebornNode.name = currentNode->mName.C_Str();
	model->nodes.push_back(rebornNode);
	int nodeIndex = model->nodes.size() - 1;

	std::vector<int> childNodesIndices;
	for (int i = 0; i < currentNode->mNumChildren; i++) {
		aiNode* childNode = currentNode->mChildren[i];
		childNodesIndices.push_back(loadChildNode(model, scene, childNode, nodeIndex));
	}
	model->nodes[nodeIndex].childIndices = childNodesIndices;

	return nodeIndex;
}

void loadNodes(Reborn::Model* model, const aiScene* scene) {
	loadChildNode(model, scene, scene->mRootNode, -1);
}

void loadModel(Reborn::Model* model, const aiScene* scene)
{
	model->meshes.reserve(scene->mNumMeshes);
	for (int i = 0; i < scene->mNumMeshes; i++) {
		const aiMesh* assimpMesh = scene->mMeshes[i];
		loadMesh(model, assimpMesh);
	}
	loadNodes(model, scene);
}

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

	loadModel(&(this->model), scene);

	for (auto& mesh : model.meshes) {
		Application::get()->renderer().create(mesh.getVAO());
	}
	
	return true;
	/*
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

		Application::get()->renderer().create(mesh.getVAO());
		loaded = true;
		return true;
	}
	return false;*/
}

bool Reborn::ModelResource::unload()
{
	for (Mesh& mesh : model.meshes) {
		Application::get()->renderer().destroy(mesh.getVAO());
	}
	loaded = false;
	return true;
}

const char* Reborn::ModelResource::getTypeStr()
{
	return "ModelResource";
}

const Reborn::Model& Reborn::ModelResource::getModel() const
{
	return model;
}

