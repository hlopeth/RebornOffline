#include "Core.h"
#include "Material.h"

Reborn::Material::Material(const Handler _programHandler):
	programHandler(_programHandler)
{
}

void Reborn::Material::setup(Renderer& renderer) const
{
	using Reborn::MaterialParameter;

	for (auto it = parameters.begin(); it != parameters.end(); it++)
	{
		const MaterialParameter& param = it->second;
		const char* paramName = it->first.c_str();
		switch (param.type)
		{
		case MaterialParameter::Type::Float:
			renderer.setUniform(programHandler, paramName, param.value.fValue);
			break;
		case MaterialParameter::Type::Int:
			renderer.setUniform(programHandler, paramName, param.value.iValue);
			break;
		case MaterialParameter::Type::tVector2:
			renderer.setUniform(programHandler, paramName, param.value.vec2Value);
			break;
		case MaterialParameter::Type::tVector3:
			renderer.setUniform(programHandler, paramName, param.value.vec3Value);
			break;
		case MaterialParameter::Type::tVector4:
			renderer.setUniform(programHandler, paramName, param.value.vec4Value);
			break;
		case MaterialParameter::Type::tMatrix2:
			renderer.setUniform(programHandler, paramName, param.value.mat2Value);
			break;
		case MaterialParameter::Type::tMatrix3:
			renderer.setUniform(programHandler, paramName, param.value.mat3Value);
			break;
		case MaterialParameter::Type::tMatrix4:
			renderer.setUniform(programHandler, paramName, param.value.mat4Value);
			break;
		case MaterialParameter::Type::Count:
			LOG_ERROR << "Reborn::Material::setup: Invalid material parameter type";
			break;
		default:
			LOG_ERROR << "Reborn::Material::setup: this shouldn't happend";
			break;
		}
	}
}

const Reborn::MaterialParameter& Reborn::Material::getParameter(const std::string& paramName) const
{
	auto search = parameters.find(paramName);
	return search->second;
}

void Reborn::Material::setParameter(const std::string& paramName, float value) {
	Reborn::MaterialParameter newParam;
	newParam.value.fValue = value;
	newParam.type = Reborn::MaterialParameter::Type::Float;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, int value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.iValue = value;
	newParam.type = Reborn::MaterialParameter::Type::Int;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Vector2 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.vec2Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tVector2;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Vector3 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.vec3Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tVector3;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Vector4 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.vec4Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tVector4;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Matrix2 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.mat2Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tMatrix2;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Matrix3 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.mat3Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tMatrix3;
	parameters[paramName] = newParam;
}

void Reborn::Material::setParameter(const std::string& paramName, Matrix4 value)
{
	Reborn::MaterialParameter newParam;
	newParam.value.mat4Value = value;
	newParam.type = Reborn::MaterialParameter::Type::tMatrix4;
	parameters[paramName] = newParam;
}

const Reborn::Handler Reborn::Material::getProgram() const
{
	return programHandler;
}
