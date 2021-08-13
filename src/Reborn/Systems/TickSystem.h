#pragma once
#include <ECS/EntitySystem.h>
#include <Components/TickComponent.h>
#include <chrono>

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class TickSystem : public EntitySystem<_ComponentCount, _SystemCount> {
	public:
		TickSystem() {
			time = std::chrono::system_clock::now();
			prevTime = time;
			setRequirements<TickComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void update() {
			updateTime();
			auto& entityManager = Application::get()->entityManager();
			for (Entity entity : getManagedEntities()) {
				auto tickComponent = entityManager.getComponent<TickComponent>(entity);
				if (tickComponent.enable) {
					tickComponent.onTick(entity, tickComponent, time.time_since_epoch().count(), delta.count());
				}
			}
		}

		uint32_t getTime() {
			return time;
		}

		uint32_t getDelta() {
			return time - prevTime;
		}
	private:
		void updateTime() {
			//Uint32 now = SDL_GetTicks();
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
			
			//если прошло слишком много времени, не обновляемся что бы не сломать физику и т.д.
			if ((now - time).count() > 1000000) {
				LOG_WARN << "TickSystem.updateTime: too mush time(" <<(now - time).count() << ") between frames.";
				time = now;
				prevTime = now - std::chrono::microseconds(1);
				delta = time - prevTime;
				return;
			}

			delta = now - time;
			prevTime = time;
			time = now;
		}

		std::chrono::time_point<std::chrono::system_clock> time;
		std::chrono::time_point<std::chrono::system_clock> prevTime;
		std::chrono::duration<double> delta;
	};
}