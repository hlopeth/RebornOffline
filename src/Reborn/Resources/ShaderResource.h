<<<<<<< HEAD:src/Reborn/Resources/ShaderResource.h
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

=======
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

>>>>>>> 13db20f3cdfe4a5f3a1991fc76db1d95a2b754e3:src/Reborn/Resources/GLSLShaderResource.h
}