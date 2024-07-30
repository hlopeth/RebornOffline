#pragma once 
#include "AbstractResource.h"
#include <Graphics/GLSLProgram.h>
#include <Graphics/Renderer.h>

namespace Reborn {
	class GLSLShaderResouce : public AbstractResource {
	public:
		GLSLShaderResouce();
		GLSLShaderResouce(const Reborn::Handler _handle);
		virtual bool tryLoad(const std::string& path) override;
		virtual bool unload() override;
		virtual const char* getTypeStr() override;
		const Handler getProgram() const;
	protected:
		Handler handle;
	};

}