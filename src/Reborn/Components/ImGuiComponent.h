#pragma once
#include "ComponentTypes.h"
#include <ECS/Entity.h>
#include <ECS/Component.h>

namespace Reborn {
	class ImGuiComponent : public Component<ImGuiComponent, ComponentTypes::ImGui>
	{
	public:
		ImGuiComponent(std::function<void(Entity, ImGuiComponent&)> _onDraw):
			enable(true),
			onDraw(_onDraw) 
		{}
		bool enable;
		std::function<void(Entity cameraControllerEntity, ImGuiComponent& _this)> onDraw;
	};
}