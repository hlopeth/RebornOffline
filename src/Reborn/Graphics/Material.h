#pragma once
#include "GLSLProgram.h"
#include <Graphics/Renderer.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>

namespace Reborn {
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

		Type type = Count;
		Value value = {0};

		MaterialParameter& operator=(const MaterialParameter& other) {
			this->type = other.type;
			memcpy(&(this->value), &(other.value), sizeof Value);
			return *this;
		}
	};

	class Material {
	public:
		Material() = delete;
		Material(const GLSLProgram& _program);
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
		const GLSLProgram& getProgram() const;
	private:
		const GLSLProgram& program;
		std::unordered_map<std::string, Reborn::MaterialParameter> parameters;
	};
}