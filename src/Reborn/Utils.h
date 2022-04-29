#pragma once
#include <Graphics/Common/Material.h>
#include <Graphics/Common/Model.h>
#include <ECS/Entity.h>

namespace Reborn {
    bool createModelEntity(
        Entity& outEntity,
        const Model& model
    );
}