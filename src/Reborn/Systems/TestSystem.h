#pragma once
#include "ECS/EntitySystem.h"
#include "Components/TestComponent.h"

namespace Reborn {
	class TestSystem : public EntitySystem {
	public:
		TestSystem() {
			setRequirements<TestComponent>();
		}
		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
			LOG_DEBUG << "TestSystem::onManagedEntityAdded";
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
			LOG_DEBUG << "TestSystem::onManagedEntityRemoved";
		};
	};
}