#pragma once
#include "ECS/EntitySystem.h"
#include "Components/TestComponent.h"

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class TestSystem : public EntitySystem<_ComponentCount, _SystemCount> {
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