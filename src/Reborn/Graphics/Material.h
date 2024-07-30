#pragma once
#include "GLSLProgram.h"
#include <Graphics/Renderer.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>

namespace Reborn {

	//default parameter names

	#define RB_MATPARAM_MODEL_TO_WORLD "uModelToWorld"
	#define RB_MATPARAM_MODEL_TO_CLIP "uModelToClip"
	#define RB_MATPARAM_AMBIENT "uAmbientColor"
	#define RB_MATPARAM_DIFFUSE "uDiffuseColor"
	#define RB_MATPARAM_SPECULAR "uSpecularColor"
	#define RB_MATPARAM_LIGHT_COLOR "uLightColor"
	#define RB_MATPARAM_OUTLINED "uOutlined"

	struct MaterialParameter {
		enum Type {
			Float,
			Int,
			tVector2,
			tVector3,
			tVector4,
			tMatrix2,
			tMatrix3,
			tMatrix4,

			Count
		};

		union Value {
			float fValue;
			int iValue;
			Vector2 vec2Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			Matrix2 mat2Value;
			Matrix3 mat3Value;
			Matrix4 mat4Value;
		};

		MaterialParameter() = default;

		MaterialParameter(const MaterialParameter& src) {
			*this = src;
		}

		MaterialParameter& operator=(const MaterialParameter& other) {
			this->type = other.type;
			memcpy(&(this->value), &(other.value), sizeof Value);
			return *this;
		}

		Type type = Count;
		Value value = { 0 };
	};

	typedef std::unordered_map<std::string, Reborn::MaterialParameter> MaterialParameters;

	class Material {
	public:
		Material() = delete;
		Material(const Handler _programHandler);
		void setup(Renderer& renderer) const;
		const MaterialParameter& getParameter(const std::string& paramName) const;
		void setParameter(const std::string& paramName, float value);
		void setParameter(const std::string& paramName, int value);
		void setParameter(const std::string& paramName, Vector2 value);
		void setParameter(const std::string& paramName, Vector3 value);
		void setParameter(const std::string& paramName, Vector4 value);
		void setParameter(const std::string& paramName, Matrix2 value);
		void setParameter(const std::string& paramName, Matrix3 value);
		void setParameter(const std::string& paramName, Matrix4 value);
		const Handler getProgram() const;
	private:
		const Handler programHandler = InvalidHandle;
		MaterialParameters parameters;
	};
}