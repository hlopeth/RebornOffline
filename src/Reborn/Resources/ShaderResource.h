#pragma once 
#include "AbstractResource.h"
#include <Graphics/Common/ShaderProgram.h>

namespace Reborn {
	class ShaderResouce : public AbstractResource {
	public:
		ShaderResouce();
		ShaderResouce(const Reborn::ShaderProgram& _program);
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;
		const ShaderProgram& getProgram() const;
	protected:
		ShaderProgram program;
	};

}