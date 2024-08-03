#include "Core.h"
#include "ModelResource.h"
#include "GLSLShaderResource.h"
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

	Reborn::MeshVertexType *vertices = new Reborn::MeshVertexType[numVertices];
	for (uint32_t i = 0; i < numVertices; i++) {
		aiVector3D v = assimpMesh->mVertices[i];
		vertices[i].position = Reborn::Vector3(v.x, v.y, v.z);

		if (assimpMesh->HasNormals()) {
			aiVector3D n = assimpMesh->mNormals[i];
			vertices[i].normal = Reborn::Vector3(n.x, n.y, n.z);
		}

		if (assimpMesh->HasTextureCoords(0)) {
			aiVector3D uv = assimpMesh->mTextureCoords[0][i];
			vertices[i].UV1 = Reborn::Vector2(uv.x, uv.y);
		}
	}

	model->meshes.emplace_back(numIndices, indices, numVertices, vertices);
}

void loadMaterial(Reborn::Model* model, const aiMaterial* assimpMaterial) {
	const auto& resManager = Reborn::Application::get()->resourceManager();
	const Reborn::GLSLShaderResouce* defaultShaderResource = resManager.getDefaultResource<Reborn::GLSLShaderResouce>();
	if (defaultShaderResource == nullptr)
		return;

	const Reborn::Handler defaultProgram = defaultShaderResource->getProgram();
	Reborn::Material material(defaultProgram);
	aiColor3D diffuseColor;
	assimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
	material.setParameter(RB_MATPARAM_DIFFUSE, Reborn::Vector3(diffuseColor.r, diffuseColor.g, diffuseColor.b));
	model->materials.push_back(material);
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
		rebornNode.numMeshes = currentNode->mNumMeshes;
		rebornNode.meshIndices.resize(currentNode->mNumMeshes);
		rebornNode.materialIndices.resize(currentNode->mNumMeshes);
		for (int i = 0; i < currentNode->mNumMeshes; i++) {
			auto meshIndex = currentNode->mMeshes[i];
			rebornNode.meshIndices[i] = meshIndex;
			rebornNode.materialIndices[i] = scene->mMeshes[meshIndex]->mMaterialIndex;
		}
	}
	else {
		rebornNode.numMeshes = 0;
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
	for (int i = 0; i < scene->mNumMaterials; i++) {
		const aiMaterial* assimpMaterial = scene->mMaterials[i];
		loadMaterial(model, assimpMaterial);
	}
	loadNodes(model, scene);
}

Reborn::ModelResource::ModelResource(): AbstractResource(0x6fc4f895)
{
}

bool Reborn::ModelResource::tryLoad(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate  | aiProcess_GenNormals);

	if (!scene) {
		LOG_ERROR 
			<< "MeshResource::tryLoad failed to read file " << path << std::endl 
			<< importer.GetErrorString();
		return false;
	}

	loadModel(&(this->model), scene);

	return true;
}

bool Reborn::ModelResource::unload()
{
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

