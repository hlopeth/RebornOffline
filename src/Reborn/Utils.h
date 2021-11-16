#pragma once
#include <Graphics/GLSLProgram.h>
#include <Graphics/Model.h>
#include <ECS/Entity.h>

namespace Reborn {
    bool createModelEntity(
        Entity& outEntity,
        const GLSLProgram& glslProgram,
        const Model& model
    );
}