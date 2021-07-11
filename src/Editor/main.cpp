#include "Reborn.h"

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

ImGuiID dockspace_id;
bool first_frame = true;

void drawDockspace(Entity entity, ImGuiComponent& _this) {
    bool p_open = true;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &p_open, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
    dockspace_id = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit", "", false))
            {
                Reborn::System::get().eventDispatcher().triggerEvent(Reborn::ApplicationShouldCloseEvent());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

void drawPropertyView(Entity entity, ImGuiComponent& _this) {
    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", &p_open, window_flags);
    ImGui::End();
}

class EditorApp : public Reborn::Application 
{
public:
    EditorApp(): Application(getWindowConfig()) {
        auto& entityManager = System::get().entityManager();

        Entity dockspaceEntity = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(dockspaceEntity);
        entityManager.addComponent<ImGuiComponent>(dockspaceEntity, std::function(drawDockspace));

        Entity propertiesViewEntity = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(propertiesViewEntity);
        entityManager.addComponent<ImGuiComponent>(propertiesViewEntity, std::function(drawPropertyView));
    }

    ~EditorApp() {

    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}