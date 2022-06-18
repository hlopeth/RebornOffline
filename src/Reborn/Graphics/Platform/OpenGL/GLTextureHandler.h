#pragma once
#include <Platform.h>
#include <Graphics/Common/TextureHandler.h>

namespace Reborn 
{
	union GLTextureParemeterValue 
	{
		FloatValue fValue;
		IntValue iValue;
		const FloatValue* fvValue;
		const IntValue* ivValue;
		const UIntValue* uivValue;
	};

	struct GLTextureParemeter 
	{
		EnumValue name;
		GLTextureParemeterValue value;
	};

	class GLTextureHandler: public TextureHandler
	{
	public:
		GLTextureHandler() : TextureHandler(0, API_TYPE) {};
		GLTextureHandler(const Vector2& _size) : TextureHandler(_size, API_TYPE) {};

		void addParameter(const GLTextureParemeter& parameter) {
			if (numParameters == 19) {
				LOG_ERROR << "Texture " << id << " has maximum amount of parameters";
			}
			parameters[numParameters] = parameter;
			numParameters++;
		}
		void addParameteri(EnumValue name, IntValue value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.iValue = value;
			addParameter(param);
		}
		void addParameterf(EnumValue name, FloatValue value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.fValue = value;
			addParameter(param);
		}
		void addParameterfv(EnumValue name, const FloatValue* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.fvValue = value;
			addParameter(param);
		}
		void addParameteriv(EnumValue name, const IntValue* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.ivValue = value;
			addParameter(param);
		}
		void addParameteruiv(EnumValue name, const UIntValue* value) {
			GLTextureParemeter param;
			param.name = name;
			param.value.uivValue = value;
			addParameter(param);
		}
		void getTextureParameters(GLTextureParemeter*& outParams, size_t& outSize) {
			outParams = parameters;
			outSize = numParameters;
		}

		EnumValue textureType; //1D, 2D, 3D or etc
		EnumValue internalFromat; //number of color components in texture
		EnumValue texelFormat; //texel data format
		EnumValue texelType; //texel data type
		UIntValue id;
	private:
		//по докам всего может быть 19 разных параметров
		GLTextureParemeter parameters[19];
		size_t numParameters = 0;
	};
}
