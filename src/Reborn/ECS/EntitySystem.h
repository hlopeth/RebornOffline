#pragma once
#include "Entity.h"
#include <bitset>

namespace Reborn {
    class EntityManager;

    class EntitySystem
    {
    public:
        virtual ~EntitySystem() = default;

    protected:
        template<typename ...Ts>
        void setRequirements() {
            (mRequirements.set(Ts::type), ...);
        };
        const std::vector<Entity>& getManagedEntities() const {
            return mManagedEntities;
        };
        virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) {};
        virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) {};

    private:
        friend EntityManager;


        void setUp(std::size_t type) {
            mType = type;
        };
        void onEntityUpdated(Entity entity, const std::bitset<REBORN_COMPONENTS_COUNT>& components) {
            bool satisfied = (mRequirements & components) == mRequirements;
            bool managed = mEntityToManagedEntity.find(entity) != std::end(mEntityToManagedEntity);

            if (satisfied && !managed) {
                addEntity(entity);
            }
            if (!satisfied && managed) {
                removeEntity(entity);
            }
        };
        void onEntityRemoved(Entity entity) {
            if (mEntityToManagedEntity.find(entity) != std::end(mEntityToManagedEntity))
                removeEntity(entity);
        };
        void addEntity(Entity entity) {
            mEntityToManagedEntity[entity] = static_cast<Index>(mManagedEntities.size());
            mManagedEntities.emplace_back(entity);
            onManagedEntityAdded(entity);
        };
        void removeEntity(Entity entity) {
            onManagedEntityRemoved(entity);
            Index index = mEntityToManagedEntity[entity];
            mEntityToManagedEntity[mManagedEntities.back()] = index;
            mEntityToManagedEntity.erase(entity);
            mManagedEntities[index] = mManagedEntities.back();
            mManagedEntities.pop_back();
        };

        std::bitset<REBORN_COMPONENTS_COUNT> mRequirements;
        std::size_t mType;
        std::vector<Entity> mManagedEntities;
        std::unordered_map<Entity, Index> mEntityToManagedEntity;
    };
}