#pragma once
#include <Core/Window.h>
#include <Core/ImGuiManager.h>
#include <Math/Vector.h>

namespace Reborn
{
	class Renderer
	{
		Renderer(Window& window, const Vector2& viewportSize);
		void beginFrame();
		void endFrame(ImGuiManager& imguiManager);
		const RenderingContext& getContext();
		Camera& getCamera();
		const Camera& getCamera() const;

		void setClearColor(const Vector3& color);
		const Vector2& getViewportSize() const;

	};
}