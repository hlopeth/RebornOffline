#pragma once
#include <Graphics/Material.h>
#include <Graphics/Model.h>
#include <ECS/Entity.h>

namespace Reborn {
    bool createModelEntity(
        Entity& outEntity,
        Material& material,
        const Model& model
    );
}