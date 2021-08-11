#pragma once
#include <Math/MathCore.h>
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
		float getAspect() const;
		float getNear() const;
		float getFar() const;
		radian getFOV() const;

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
	};
}