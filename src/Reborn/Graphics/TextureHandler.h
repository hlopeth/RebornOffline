#pragma once
#include "Platform.h"

namespace Reborn {
	union TextureParemeterValue {
		FloatValue fValue;
		IntValue iValue;
		const FloatValue* fvValue;
		const IntValue* ivValue;
		const UIntValue* uivValue;
	};

	struct TextureParemeter {
		EnumValue name;
		TextureParemeterValue value;
	};

	class TextureHandler
	{
	public:
		EnumValue textureType; //1D, 2D, 3D or etc
		EnumValue internalFromat; //number of color components in texture
		EnumValue texelFormat; //texel data format
		EnumValue texelType; //texel data type
		SizeiValue width;
		SizeiValue height;
		UIntValue id;
		void addParameter(const TextureParemeter& parameter) {
			if (numParameters == 19) {
				LOG_ERROR << "Texture " << id << " has maximum amount of parameters";
			}
			parameters[numParameters] = parameter;
			numParameters++;
		}
		void addParameteri(EnumValue name, IntValue value) {
			TextureParemeter param;
			param.name = name;
			param.value.iValue = value;
			addParameter(param);
		}
		void addParameterf(EnumValue name, FloatValue value) {
			TextureParemeter param;
			param.name = name;
			param.value.fValue = value;
			addParameter(param);
		}
		void addParameterfv(EnumValue name, const FloatValue* value) {
			TextureParemeter param;
			param.name = name;
			param.value.fvValue = value;
			addParameter(param);
		}
		void addParameteriv(EnumValue name, const IntValue* value) {
			TextureParemeter param;
			param.name = name;
			param.value.ivValue = value;
			addParameter(param);
		}
		void addParameteruiv(EnumValue name, const UIntValue* value) {
			TextureParemeter param;
			param.name = name;
			param.value.uivValue = value;
			addParameter(param);
		}
		void getTextureParameters(TextureParemeter*& outParams, size_t& outSize) {
			outParams = parameters;
			outSize = numParameters;
		}
	private:
		//по докам всего может быть 19 разных параметров
		TextureParemeter parameters[19];
		size_t numParameters = 0;
	};
}