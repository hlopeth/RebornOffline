#include <Core.h>
#include "Renderer.h"

namespace Reborn
{
	Renderer::Renderer(Window& _window, const Vector2& _viewportSize, APIType _apiType):
		window(_window),
		viewportSize(_viewportSize),
		camera(Reborn::toRadians(60), 1, 100, 1),
		apiType(_apiType)
	{}

	Camera& Renderer::getCamera()
	{
		return camera;
	}

	const Camera& Renderer::getCamera() const
	{
		return camera;
	}

	void Renderer::setClearColor(const Vector3& color)
	{
		clearColor = color;
	}

	const Vector3& Renderer::getClearColor() const
	{
		return clearColor;
	}

	const Vector2& Renderer::getViewportSize() const
	{
		return viewportSize;
	}

	const Vector2& Renderer::getViewportSize(const Vector2& newSize)
	{
		return viewportSize;
	}

	APIType Reborn::Renderer::getAPIType() const
	{
		return apiType;
	}
}