#pragma once
#include "AbstractResource.h"
#include "Graphics/Model.h"

namespace Reborn {
	class ModelResource : public AbstractResource {
	public:
		ModelResource();
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;

		const Model& getModel() const;
	private:
		Model model;
	};
}