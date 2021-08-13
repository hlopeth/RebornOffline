#pragma once
#include "Entity.h"

namespace Reborn
{
	template<std::size_t ComponentCount, std::size_t SystemCount>
	class EntityContainer
	{
	public:
		std::vector<std::bitset<ComponentCount>>& getEntityToBitset() {
			return mEntityToBitset;
		}
		const std::bitset<ComponentCount>& getBitset(Entity cameraControllerEntity) const {
			return mEntityToBitset[cameraControllerEntity];
		}
		Entity create() {
			Entity cameraControllerEntity = Entity();
			//по возможности переиспользует id из mFreeEntities
			if (mFreeEntities.empty()) {
				cameraControllerEntity = static_cast<Entity>(mEntityToBitset.size()); //entity = последний возможный id
				mEntityToBitset.emplace_back();
			}
			else {
				cameraControllerEntity = mFreeEntities.back();
				mFreeEntities.pop_back();
				mEntityToBitset[cameraControllerEntity].reset();
			}
			return cameraControllerEntity;
		}
		void remove(Entity cameraControllerEntity) {
			mFreeEntities.push_back(cameraControllerEntity);
		}

	private:
		std::vector<std::bitset<ComponentCount>> mEntityToBitset;
		std::vector<Entity> mFreeEntities;
	};
}