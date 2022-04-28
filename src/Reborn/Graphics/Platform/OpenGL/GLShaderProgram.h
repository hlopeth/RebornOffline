#pragma once
#include "Platform.h"
#include "Graphics/Common/ShaderProgram.h"

namespace Reborn 
{
	class GLShaderProgram: public ShaderProgram 
	{
	public:
		GLShaderProgram(): ShaderProgram(API_TYPE) {};
		GLShaderProgram(UIntValue _id): ShaderProgram(API_TYPE), id(_id) {};
		UIntValue id = -1;
	};
}