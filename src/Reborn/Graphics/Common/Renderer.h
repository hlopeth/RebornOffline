#pragma once
#include <Core/Window.h>
#include <Core/ImGuiManager.h>
#include <Math/Vector.h>
#include "APIType.h"
#include "Camera.h"

namespace Reborn
{
	class Renderer
	{
	public:
		Renderer(Window& window, const Vector2& viewportSize, APIType apiType);
		Camera& getCamera();
		const Camera& getCamera() const;

		void setClearColor(const Vector3& color);
		const Vector3& getClearColor() const;

		const Vector2& getViewportSize() const;
		const Vector2& getViewportSize(const Vector2& newSize);

		APIType getAPIType() const;
	private:
		Vector2 viewportSize;
		Camera camera;
		Window& window;
		Vector3 clearColor;
		APIType apiType;
	};
}