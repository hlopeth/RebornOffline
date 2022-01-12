#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

namespace Reborn {
	class Model {
	public:
		struct Node {
			std::string name = "";
			size_t numMeshes = 0;
			std::vector<int> meshIndices;
			std::vector<int> materialIndices;
			int transformIndex = -1;
			int parentIndex = -1;
			std::vector<int> childIndices;
		};
		std::vector<Mesh> meshes;
		std::vector<Transform> transforms;
		std::vector<Model::Node> nodes;
		std::vector<Material> materials;
	};
}