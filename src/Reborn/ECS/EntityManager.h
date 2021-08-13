#pragma once
#include "Entity.h"
#include "ComponentContainer.h"
#include "EntityContainer.h"
#include "EntitySystem.h"
#include <array>

//heavily inspierd by https://github.com/pvigier/ecs

namespace Reborn {
    template<std::size_t ComponentCount, std::size_t SystemCount>
    class EntityManager
    {
    public:
        template<typename T>
        void registerComponent() {
            checkComponentType<T>();
            mComponentContainers[T::type] = 
                std::make_unique<ComponentContainer<T, ComponentCount, SystemCount>>(mEntities.getEntityToBitset());
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

        void removeEntity(Entity cameraControllerEntity) {
            // Remove components
            for (std::size_t i = 0; i < ComponentCount; ++i)
            {
                if (mComponentContainers[i])
                    mComponentContainers[i]->tryRemove(cameraControllerEntity);
            }
            // Send message to systems
            for (auto& system : mSystems)
                system->onEntityRemoved(cameraControllerEntity);
            // Remove entity
            mEntities.remove(cameraControllerEntity);
        };

        template<typename T>
        bool hasComponent(Entity cameraControllerEntity) const {
            checkComponentType<T>();
            return mEntities.getBitset(cameraControllerEntity)[T::type];
        };

        template<typename ...Ts>
        bool hasComponents(Entity cameraControllerEntity) const {
            checkComponentTypes<Ts...>();
            auto requirements = std::bitset<ComponentCount>();
            (requirements.set(Ts::type), ...);
            return (requirements & mEntities.getBitset(cameraControllerEntity)) == requirements;
        };

        template<typename T>
        T& getComponent(Entity cameraControllerEntity) {
            checkComponentType<T>();
            return getComponentContainer<T>()->get(cameraControllerEntity);
        };

        template<typename T>
        const T& getComponent(Entity cameraControllerEntity) const {
            checkComponentType<T>();
            return getComponentContainer<T>()->get(cameraControllerEntity);
        };

        template<typename ...Ts>
        std::tuple<Ts&...> getComponents(Entity cameraControllerEntity) {
            checkComponentTypes<Ts...>();
            return std::tie(getComponentContainer<Ts>()->get(cameraControllerEntity)...);
        };

        template<typename ...Ts>
        std::tuple<const Ts&...> getComponents(Entity cameraControllerEntity) const {
            checkComponentTypes<Ts...>();
            return std::tie(getComponentContainer<Ts>()->get(cameraControllerEntity)...);
        };

        template<typename T, typename... Args>
        void addComponent(Entity cameraControllerEntity, Args&&... args) {
            checkComponentType<T>();
            getComponentContainer<T>()->add(cameraControllerEntity, std::forward<Args>(args)...);
            // Send message to systems
            const auto& bitset = mEntities.getBitset(cameraControllerEntity);
            for (auto& system : mSystems)
                system->onEntityUpdated(cameraControllerEntity, bitset);
        };

        template<typename T>
        void removeComponent(Entity cameraControllerEntity) {
            checkComponentType<T>();
            getComponentContainer<T>()->remove(cameraControllerEntity);
            // Send message to systems
            const auto& bitset = mEntities.getBitset(cameraControllerEntity);
            for (auto& system : mSystems)
                system->onEntityUpdated(cameraControllerEntity, bitset);
        };

        template<typename T>
        Entity getOwner(const T& component) const {
            checkComponentType<T>();
            return getComponentContainer<T>()->getOwner(component);
        };

    private:
        template<typename T>
        void checkComponentType() const { 
            static_assert(T::type < ComponentCount);
        };
        template<typename ...Ts>
        void checkComponentTypes() const {
            (checkComponentType<Ts>(), ...);
        };

        template<typename T>
        auto getComponentContainer() {
            return static_cast<ComponentContainer<T, ComponentCount, SystemCount>*>(mComponentContainers[T::type].get());
        };
        template<typename T>
        auto getComponentContainer() const {
            return static_cast<ComponentContainer<T, ComponentCount, SystemCount>*>(mComponentContainers[T::type].get());
        };

        std::array<std::unique_ptr<BaseComponentContainer>, ComponentCount> mComponentContainers;
        EntityContainer<ComponentCount, SystemCount> mEntities;
        std::vector<std::unique_ptr<EntitySystem<ComponentCount, SystemCount>>> mSystems;
    };
}