#pragma once
#include "AbstractResource.h"
#include "Graphics/Mesh.h"

namespace Reborn {
	class ModelResource : public AbstractResource {
	public:
		ModelResource();
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		const Mesh& getMesh() const;
	private:
		Mesh mesh;
	};
}