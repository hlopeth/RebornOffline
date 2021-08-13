#pragma once
#include "Entity.h"
#include "BaseComponentContainer.h"

namespace Reborn {
    template<typename T, std::size_t ComponentCount, std::size_t SystemCount>
    class ComponentContainer : public BaseComponentContainer
    {
    public:
        ComponentContainer(std::vector<std::bitset<ComponentCount>>& entityToBitset) :
            mEntityToBitset(entityToBitset) {

        }

        T& get(Entity cameraControllerEntity) {
            return mComponents[mEntityToComponent[cameraControllerEntity]];
        };
        const T& get(Entity cameraControllerEntity) const {
            return mComponents[mEntityToComponent[cameraControllerEntity]];
        };
        template<typename... Args>
        void add(Entity cameraControllerEntity, Args&&... args) {
            Index index = static_cast<Index>(mComponents.size());
            mComponents.emplace_back(std::forward<Args>(args)...);
            mComponentToEntity.emplace_back(cameraControllerEntity);
            mEntityToComponent[cameraControllerEntity] = index;
            mEntityToBitset[cameraControllerEntity][T::type] = true;
        };
        void remove(Entity cameraControllerEntity) {
            mEntityToBitset[cameraControllerEntity][T::type] = false;
            Index index = mEntityToComponent[cameraControllerEntity];
            // Update mComponents
            mComponents[index] = std::move(mComponents.back());
            mComponents.pop_back();
            // Update mEntityToComponent
            mEntityToComponent[mComponentToEntity.back()] = index;
            mEntityToComponent.erase(cameraControllerEntity);
            // Update mComponentToEntity
            mComponentToEntity[index] = mComponentToEntity.back();
            mComponentToEntity.pop_back();
        }
        virtual bool tryRemove(Entity cameraControllerEntity) override {
            if (mEntityToBitset[cameraControllerEntity][T::type])
            {
                remove(cameraControllerEntity);
                return true;
            }
            return false;
        };
        Entity getOwner(const T& component) const {
            auto begin = mComponents.data();
            auto index = static_cast<std::size_t>(&component - begin);
            return mComponentToEntity[index];
        };

    private:
        std::vector<T> mComponents;
        std::vector<Entity> mComponentToEntity;
        std::unordered_map<Entity, Index> mEntityToComponent;
        std::vector<std::bitset<ComponentCount>>& mEntityToBitset;
    };
}