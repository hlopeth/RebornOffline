#pragma once
#include "Entity.h"

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
        virtual void onManagedEntityAdded([[maybe_unused]] Entity cameraControllerEntity) {};
        virtual void onManagedEntityRemoved([[maybe_unused]] Entity cameraControllerEntity) {};

    private:
        friend EntityManager;


        void setUp(std::size_t type) {
            mType = type;
        };
        void onEntityUpdated(Entity cameraControllerEntity, const std::bitset<REBORN_COMPONENTS_COUNT>& components) {
            bool satisfied = (mRequirements & components) == mRequirements;
            bool managed = mEntityToManagedEntity.find(cameraControllerEntity) != std::end(mEntityToManagedEntity);

            if (satisfied && !managed) {
                addEntity(cameraControllerEntity);
            }
            if (!satisfied && managed) {
                removeEntity(cameraControllerEntity);
            }
        };
        void onEntityRemoved(Entity cameraControllerEntity) {
            if (mEntityToManagedEntity.find(cameraControllerEntity) != std::end(mEntityToManagedEntity))
                removeEntity(cameraControllerEntity);
        };
        void addEntity(Entity cameraControllerEntity) {
            mEntityToManagedEntity[cameraControllerEntity] = static_cast<Index>(mManagedEntities.size());
            mManagedEntities.emplace_back(cameraControllerEntity);
            onManagedEntityAdded(cameraControllerEntity);
        };
        void removeEntity(Entity cameraControllerEntity) {
            onManagedEntityRemoved(cameraControllerEntity);
            Index index = mEntityToManagedEntity[cameraControllerEntity];
            mEntityToManagedEntity[mManagedEntities.back()] = index;
            mEntityToManagedEntity.erase(cameraControllerEntity);
            mManagedEntities[index] = mManagedEntities.back();
            mManagedEntities.pop_back();
        };

        std::bitset<REBORN_COMPONENTS_COUNT> mRequirements;
        std::size_t mType;
        std::vector<Entity> mManagedEntities;
        std::unordered_map<Entity, Index> mEntityToManagedEntity;
    };
}