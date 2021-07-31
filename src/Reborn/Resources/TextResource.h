#pragma once
#include "AbstractResource.h"

namespace Reborn {
	class TextResource : public AbstractResource {
	public:
		TextResource();
		virtual bool tryLoad(const std::string & path) override;
		virtual bool unload() override;
		const std::string& getText() const;
	private:
		std::string text;
	};
}