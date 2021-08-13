#pragma once

namespace Reborn {
    class BaseComponentContainer
    {
    public:
        virtual ~BaseComponentContainer() = default;

        virtual bool tryRemove(Entity cameraControllerEntity) = 0;
    };
}