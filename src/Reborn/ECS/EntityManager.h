#pragma once
#include "Entity.h"
#include "ComponentContainer.h"
#include "EntityContainer.h"
#include "EntitySystem.h"
#include <Components/Transform3DComponent.h>
#include <array>

//heavily inspierd by https://github.com/pvigier/ecs

namespace Reborn {
    class EntityManager
    {
    public:
        template<typename T>
        void registerComponent() {
            checkComponentType<T>();
            mComponentContainers[T::type] = 
                std::make_unique<ComponentContainer<T>>(mEntities.getEntityToBitset());
        };

        template<typename T, typename ...Args>
        T* createSystem(Args&& ...args) {
            auto type = mSystems.size();
            auto& system = mSystems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            system->setUp(type);
            return static_cast<T*>(system.get());
        };

        Entity createEntity() {
            return mEntities.create();
        };

        void removeEntity(Entity entity, bool removeChilds = true) {
            if (removeChilds && this->hasComponent<Transform3DComponent>(entity)) {
                const auto& tr3d = this->getComponent<Transform3DComponent>(entity);
                auto childs = tr3d.getChilds();
                for (Entity child : childs) {
                    this->getComponent<Transform3DComponent>(child).setParent(NoEntity);
                    this->removeEntity(child, true);
                }
            }

            // Send message to systems
            for (auto& system : mSystems)
                system->onEntityRemoved(entity);

            // Remove components
            for (std::size_t i = 0; i < REBORN_COMPONENTS_COUNT; ++i)
            {
                if (mComponentContainers[i])
                    mComponentContainers[i]->tryRemove(entity);
            }
            // Remove entity
            mEntities.remove(entity);
        };

        template<typename T>
        bool hasComponent(Entity entity) const {
            checkComponentType<T>();
            return mEntities.getBitset(entity)[T::type];
        };

        template<typename ...Ts>
        bool hasComponents(Entity entity) const {
            checkComponentTypes<Ts...>();
            auto requirements = std::bitset<REBORN_COMPONENTS_COUNT>();
            (requirements.set(Ts::type), ...);
            return (requirements & mEntities.getBitset(entity)) == requirements;
        };

        template<typename T>
        T& getComponent(Entity entity) {
            checkComponentType<T>();
            return getComponentContainer<T>()->get(entity);
        };

        template<typename T>
        const T& getComponent(Entity entity) const {
            checkComponentType<T>();
            return getComponentContainer<T>()->get(entity);
        };

        template<typename ...Ts>
        std::tuple<Ts&...> getComponents(Entity entity) {
            checkComponentTypes<Ts...>();
            return std::tie(getComponentContainer<Ts>()->get(entity)...);
        };

        template<typename ...Ts>
        std::tuple<const Ts&...> getComponents(Entity entity) const {
            checkComponentTypes<Ts...>();
            return std::tie(getComponentContainer<Ts>()->get(entity)...);
        };

        template<typename T, typename... Args>
        const T& addComponent(Entity entity, Args&&... args) {
            checkComponentType<T>();
            getComponentContainer<T>()->add(entity, std::forward<Args>(args)...);
            // Send message to systems
            const auto& bitset = mEntities.getBitset(entity);
            for (auto& system : mSystems)
                system->onEntityUpdated(entity, bitset);
            return getComponent<T>(entity);
        };

        template<typename T>
        void removeComponent(Entity entity) {
            checkComponentType<T>();
            getComponentContainer<T>()->remove(entity);
            // Send message to systems
            const auto& bitset = mEntities.getBitset(entity);
            for (auto& system : mSystems)
                system->onEntityUpdated(entity, bitset);
        };

        template<typename T>
        Entity getOwner(const T& component) const {
            checkComponentType<T>();
            return getComponentContainer<T>()->getOwner(component);
        };

    private:
        template<typename T>
        void checkComponentType() const { 
            static_assert(T::type < REBORN_COMPONENTS_COUNT);
        };
        template<typename ...Ts>
        void checkComponentTypes() const {
            (checkComponentType<Ts>(), ...);
        };

        template<typename T>
        auto getComponentContainer() {
            return static_cast<ComponentContainer<T>*>(mComponentContainers[T::type].get());
        };
        template<typename T>
        auto getComponentContainer() const {
            return static_cast<ComponentContainer<T>*>(mComponentContainers[T::type].get());
        };

        std::array<std::unique_ptr<BaseComponentContainer>, REBORN_COMPONENTS_COUNT> mComponentContainers;
        EntityContainer mEntities;
        std::vector<std::unique_ptr<EntitySystem>> mSystems;
    };
}