#pragma once
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Utils.h>

namespace Reborn {
	class UpdateTransformSystem : public EntitySystem {
	public:
		UpdateTransformSystem(EntityManager& _entityManager) : entityManager(_entityManager) {
			setRequirements<Transform3DComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void update() {
			const auto& me = getManagedEntities();
			for (Entity entity : me) {
				auto& transform3DComponent = entityManager.getComponent<Transform3DComponent>(entity);
				transform3DComponent.world = getWorldMatrix(transform3DComponent);
			}
		};
	private:
		EntityManager& entityManager;

		Matrix4 getWorldMatrix(const Transform3DComponent& tr3d) {
			Matrix4 res = tr3d.getModelMatrix();
			const Transform3DComponent* currTr3d = nullptr;

			for (Entity i = tr3d.getParent(); i != NoEntity; i = currTr3d->getParent()) {
				currTr3d = &entityManager.getComponent<Transform3DComponent>(i);
				res = currTr3d->getModelMatrix() * res;
			}
			return res;
		}
	};
}