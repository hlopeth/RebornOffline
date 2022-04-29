#pragma once 
#include <Platform.h>
#include "AbstractResource.h"
#include <Graphics/Common/ShaderProgram.h>
#include <Graphics/Common/Renderer.h>

#ifdef REBORN_OPENGL
#include <Graphics/Platform/OpenGL/GLShaderProgram.h>
#endif // REBORN_OPENGL


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
#ifdef REBORN_OPENGL
		GLShaderProgram program;
#else
		ShaderProgram program;
#endif // REBORN_OPENGL

	};

}