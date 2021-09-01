#pragma once
#include "AbstractResource.h"

namespace Reborn {
	class MeshResource : public AbstractResource {
	public:
		MeshResource();
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
	};
}