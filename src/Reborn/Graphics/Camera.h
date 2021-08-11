#pragma once
#include <Math/MathCore.h>
#include <Math/Vector3.h>
#include <Math/Matrix4.h>

namespace Reborn {
	class Camera {
	public:
		Camera();
		Camera(radian fov, float _aspect, float _near, float _far);
		const Matrix4& getProjection() const;
		const Matrix4& getViewProjection() const;
		const Matrix4& getView() const;
		void setAspect(float newAspect);
		void setNear(float newNear);
		void setFar(float newFar);
		void setFOV(radian fov);
		void setPosition(const Vector3 newPosition);
		void setCursor(const Vector3 newCursor);
		float getAspect() const;
		float getNear() const;
		float getFar() const;
		radian getFOV() const;
		Vector3 getPosition() const;
		Vector3 getCursor() const;

	private:
		void rebuildMatrices();
		bool matricesDirty;
		Matrix4 proj;
		Matrix4 view;
		Matrix4 viewProj;

		radian fov;
		float aspect;
		float _near;
		float _far;
		Vector3 position;
		Vector3 cursor;
	};
}