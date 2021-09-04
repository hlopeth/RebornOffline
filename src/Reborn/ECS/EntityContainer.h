#pragma once
#include "Entity.h"

namespace Reborn
{
	class EntityContainer
	{
	public:
		std::vector<std::bitset<REBORN_COMPONENTS_COUNT>>& getEntityToBitset() {
			return mEntityToBitset;
		}
		const std::bitset<REBORN_COMPONENTS_COUNT>& getBitset(Entity entity) const {
			return mEntityToBitset[entity];
		}
		Entity create() {
			Entity entity = Entity();
			//по возможности переиспользует id из mFreeEntities
			if (mFreeEntities.empty()) {
				entity = static_cast<Entity>(mEntityToBitset.size()); //entity = последний возможный id
				mEntityToBitset.emplace_back();
			}
			else {
				entity = mFreeEntities.back();
				mFreeEntities.pop_back();
				mEntityToBitset[entity].reset();
			}
			return entity;
		}
		void remove(Entity entity) {
			mFreeEntities.push_back(entity);
		}

	private:
		std::vector<std::bitset<REBORN_COMPONENTS_COUNT>> mEntityToBitset;
		std::vector<Entity> mFreeEntities;
	};
}