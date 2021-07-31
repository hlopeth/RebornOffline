#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	union GLTextureParemeterValue {
		GLfloat fValue;
		GLint iValue;
		const GLfloat* fvValue;
		const GLint* ivValue;
		const GLuint* uivValue;
	};

	struct GLTextureParemeter {
		GLenum name;
		GLTextureParemeterValue value;
	};

	class GLTexture
	{
	public:
		GLenum textureType; //1D, 2D, 3D or etc
		GLenum internalFromat; //number of color components in texture
		GLenum texelFormat; //texel data format
		GLenum texelType; //texel data type
		GLsizei width;
		GLsizei height;
		GLuint id;
		void addParameter(const GLTextureParemeter& parameter) {
			if (numParameters == 19) {
				LOG_ERROR << "Texture " << id << " has maximum amount of parameters";
			}
			parameters[numParameters] = parameter;
			numParameters++;
		}
		void addParameteri(GLenum name, GLint value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.iValue = value;
			addParameter(param);
		}
		void addParameterf(GLenum name, GLfloat value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.fValue = value;
			addParameter(param);
		}
		void addParameterfv(GLenum name, const GLfloat* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.fvValue = value;
			addParameter(param);
		}
		void addParameteriv(GLenum name, const GLint* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.ivValue = value;
			addParameter(param);
		}
		void addParameteruiv(GLenum name, const GLuint* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.uivValue = value;
			addParameter(param);
		}
		void getTextureParameters(GLTextureParemeter*& outParams, size_t& outSize) {
			outParams = parameters;
			outSize = numParameters;
		}
	private:
		//по докам всего может быть 19 разных параметров
		GLTextureParemeter parameters[19];
		size_t numParameters = 0;
	};
}