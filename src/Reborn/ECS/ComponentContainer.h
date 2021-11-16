#pragma once
#include "Entity.h"
#include "BaseComponentContainer.h"

namespace Reborn {
    template<typename T>
    class ComponentContainer : public BaseComponentContainer
    {
    public:
        ComponentContainer(std::vector<std::bitset<REBORN_COMPONENTS_COUNT>>& entityToBitset) :
            mEntityToBitset(entityToBitset) {
            mComponents.reserve(REBORN_COMPONENTS_COUNT);
        }

        T& get(Entity entity) {
            return mComponents[mEntityToComponent[entity]];
        };
        const T& get(Entity entity) const {
            return mComponents[mEntityToComponent[entity]];
        };
        template<typename... Args>
        void add(Entity entity, Args&&... args) {
            Index index = static_cast<Index>(mComponents.size());
            mComponents.emplace_back(std::forward<Args>(args)...);
            mComponentToEntity.emplace_back(entity);
            mEntityToComponent[entity] = index;
            mEntityToBitset[entity][T::type] = true;
        };
        void remove(Entity entity) {
            mEntityToBitset[entity][T::type] = false;
            Index index = mEntityToComponent[entity];
            // Update mComponents
            mComponents[index] = std::move(mComponents.back());
            mComponents.pop_back();
            // Update mEntityToComponent
            mEntityToComponent[mComponentToEntity.back()] = index;
            mEntityToComponent.erase(entity);
            // Update mComponentToEntity
            mComponentToEntity[index] = mComponentToEntity.back();
            mComponentToEntity.pop_back();
        }
        virtual bool tryRemove(Entity entity) override {
            if (mEntityToBitset[entity][T::type])
            {
                remove(entity);
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
        std::vector<std::bitset<REBORN_COMPONENTS_COUNT>>& mEntityToBitset;
    };
}