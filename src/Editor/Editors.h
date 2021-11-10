#pragma once
#include "Reborn.h"

using namespace Reborn;

void transform3dEditor(Transform3DComponent& transform, float speed = 0.1) {
    if (ImGui::TreeNode("Transform3DComponent")) {
        Vector3 pos = transform.getPosition();
        Vector3 scale = transform.getScale();

        ImGui::DragFloat3("position", pos.d, speed);
        ImGui::DragFloat3("scale", scale.d, speed);
        Vector3 rotation 
            = Vector3(
                toDegrees(transform.getRotation().x),
                toDegrees(transform.getRotation().y),
                toDegrees(transform.getRotation().z)
            ); 
        ImGui::DragFloat3("rotation", rotation.d, 1);
        transform.setPosition(pos);
        transform.setScale(scale);
        transform.setRotation(Vector3(toRadians(rotation.x), toRadians(rotation.y), toRadians(rotation.z)));
        ImGui::TreePop();
    }
}

void cameraEditor(Camera& camera) {
    if (ImGui::TreeNode("Camera")) {
        Vector3 position = camera.getPosition();
        ImGui::DragFloat3("position", position.d, 0.1);
        camera.setPosition(position);

        Vector3 cursor = camera.getCursor();
        ImGui::DragFloat3("cursor", cursor.d, 0.1);
        camera.setCursor(cursor);

        float fov = camera.getFOV();
        ImGui::SliderAngle("fov", &fov, 10, 170);
        camera.setFOV(fov);

        float valNear = camera.getNear();
        ImGui::SliderFloat("near", &valNear, -30, 30, "%.2f");
        camera.setNear(valNear);

        float valFar = camera.getFar();
        ImGui::SliderFloat("far", &valFar, -30, 30, "%.2f");
        camera.setFar(valFar);
        ImGui::TreePop();
    }
}