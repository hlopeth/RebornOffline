#include "Core.h"
#include "Utils.h"
#include <Core/Application.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>

using namespace Reborn;

std::vector<const Mesh*> tempMeshContainer;
 
void createChildNodelEntity(
    Entity& outEntity,
    const GLSLProgram& glslProgram,
    const Model& model,
    int nodeIndex,
    const Entity parent
) {
    const Model::Node& node = model.nodes[nodeIndex];

    auto& entityManager = Application::get()->entityManager();

    //создаем ноду
    outEntity = entityManager.createEntity();
    entityManager.addComponent<Transform3DComponent>(outEntity, model.transforms[node.transformIndex]);
    Transform3DComponent& transform = entityManager.getComponent<Transform3DComponent>(outEntity);
    if (node.numMeshes > 0) {
        tempMeshContainer.resize(node.numMeshes);
        for (size_t i = 0; i < node.numMeshes; i++)
        {
            tempMeshContainer[i] = &(model.meshes[node.meshIndices[i]]);
        }
        entityManager.addComponent<RenderComponent>(outEntity, tempMeshContainer.data(), node.numMeshes, glslProgram);
    }
    if (parent != -1) {
        transform.setParent(parent);
    }
    
    for (int i = 0; i < node.childIndices.size(); i++) {
        Entity childeEntity = entityManager.createEntity();
        createChildNodelEntity(childeEntity, glslProgram, model, node.childIndices[i], outEntity);
    }
}

bool Reborn::createModelEntity(
    Entity& outEntity,
    const GLSLProgram& glslProgram,
    const Model& model
)
{
    if (model.nodes.size() < 1) {
        return false;
    }
    createChildNodelEntity(outEntity, glslProgram, model, 0, -1);
    return true;
}