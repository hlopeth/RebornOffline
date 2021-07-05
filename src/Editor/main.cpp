#include "Reborn.h"
#include "Components/Transform3DComponent.h"
#include "Components/ImGuiComponent.h"
#include <imgui.h>

using namespace Reborn;

Reborn::WindowConfiguration getWindowConfig() {
    Reborn::WindowConfiguration defaultConfig = { "Editor" };
    defaultConfig.x = 100;
    defaultConfig.y = 100;
    defaultConfig.width = 800;
    defaultConfig.height = 600;
    defaultConfig.resizable = true;

    return defaultConfig;
}

void drawDemoWindow(Entity entity, ImGuiComponent& _this) {
    ImGui::ShowDemoWindow();
}

void drawMetricsWindow(Entity entity, ImGuiComponent& _this) {
    ImGui::ShowMetricsWindow();
}

void drawStyleEditor(Entity entity, ImGuiComponent& _this) {
    ImGui::ShowStyleEditor();
}

class EditorApp : public Reborn::Application 
{
public:
    EditorApp(): Application(getWindowConfig()) {
        auto& entityManager = System::get().entityManager();

        Entity entity1 = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(entity1, 10.f, 10.f, 10.f);
        entityManager.addComponent<ImGuiComponent>(entity1, std::function<void(Entity, ImGuiComponent&)>(drawDemoWindow));

        Entity entity2 = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(entity2, 10.f, 10.f, 10.f);
        entityManager.addComponent<ImGuiComponent>(entity2, std::function<void(Entity, ImGuiComponent&)>(drawMetricsWindow));

        Entity entity3 = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(entity3, 10.f, 10.f, 10.f);
        entityManager.addComponent<ImGuiComponent>(entity3, std::function<void(Entity, ImGuiComponent&)>(drawStyleEditor));
    }

    ~EditorApp() {

    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}