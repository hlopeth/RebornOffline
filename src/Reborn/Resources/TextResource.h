#pragma once
#include "AbstractResource.h"

namespace Reborn {
	class TextResource : public AbstractResource {
	public:
		TextResource();
		TextResource(std::string text);
		virtual bool tryLoad(const std::string & path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;
		const std::string& getText() const;
	private:
		std::string text;
	};
}