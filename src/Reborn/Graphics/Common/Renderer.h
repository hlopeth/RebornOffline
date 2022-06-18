#pragma once
#include <Core/Window.h>
#include <Core/ImGuiManager.h>
#include <Math/Vector.h>
#include "APIType.h"
#include "Camera.h"

struct ImDrawData;

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
		const Vector2& setViewportSize(const Vector2& newSize);

		APIType getAPIType() const;

		virtual bool initImGui(SDL_Window* window);
		virtual void newImGuiFrame();
		virtual void destroyImGui();
		virtual void drawImGui(ImDrawData* drawData);
	private:
		Vector2 viewportSize;
		Camera camera;
		Window& window;
		Vector3 clearColor;
		APIType apiType;
	};
}