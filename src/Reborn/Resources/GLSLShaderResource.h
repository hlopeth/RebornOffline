#pragma once 
#include "AbstractResource.h"
#include <Graphics/ShaderProgram.h>
#include <Graphics/Renderer.h>

namespace Reborn {
	class GLSLShaderResouce : public AbstractResource {
	public:
		GLSLShaderResouce();
		GLSLShaderResouce(const Reborn::ShaderProgram& _program);
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;
		const ShaderProgram& getProgram() const;
	protected:
		ShaderProgram program;
	};

}