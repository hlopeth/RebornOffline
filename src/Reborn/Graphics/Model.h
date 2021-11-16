#pragma once
#include "Mesh.h"
#include "Transform.h"

namespace Reborn {
	class Model {
	public:
		struct Node {
			std::string name = "";
			int meshIndex = -1;
			int transformIndex = -1;
			int parentIndex = -1;
			std::vector<int> childIndices;
		};
		std::vector<Mesh> meshes;
		std::vector<Transform> transforms;
		std::vector<Model::Node> nodes;
	};
}