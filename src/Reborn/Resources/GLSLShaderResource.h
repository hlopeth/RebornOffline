#pragma once 
#include "AbstractResource.h"
#include <Graphics/GLSLProgram.h>
#include <Graphics/Renderer.h>

namespace Reborn {
	class GLSLShaderResouce : public AbstractResource {
	public:
		GLSLShaderResouce();
		GLSLShaderResouce(const Reborn::GLSLProgram& _program);
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;
		const GLSLProgram& getProgram() const;
	protected:
		GLSLProgram program;
	};

}