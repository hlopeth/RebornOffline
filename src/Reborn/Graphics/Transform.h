#pragma once
#include "Math/Vector.h"
#include "Math/Matrix4.h"

namespace Reborn {
	class Transform {
	public:
		Transform() : position(0.f), scale(1.f), rotation(0.f) {}
		Transform(
			const Vector3& _position,
			const Vector3& _scale,
			const Vector3& _rotation
		);
		const Vector3& getPosition() const;
		const Vector3& getScale() const;
		const Vector3& getRotation() const;
		const Matrix4& getModelMatrix() const;
		const Matrix4& getModelMatrix(const Matrix4& parentModel) const;
		void setPosition(Vector3 newPosition);
		void setScale(Vector3 newScale);
		void setRotation(Vector3 newRotation);
	private:
		Vector3 position;
		Vector3 scale;
		Vector3 rotation;
		Matrix4 model;
		bool modelMatrixIsDirty = true;
	};
}