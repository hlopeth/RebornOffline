#include "Reborn.h"

#include "TestVector.h"
#include "TestMatrix.h"

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

Reborn::Renderer* renderer_ptr = nullptr;

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
    static ImVec4 color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", &p_open, window_flags);
    ImGui::ColorPicker4("Background", (float*)&color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

    const char* items[] = { "128x128", "256x256", "512x512", "1024x1024", "2048x2048"};
    Vector2 rects[] = { Vector2(128,128), Vector2(256,256), Vector2(512,512), Vector2(1024,1024), Vector2(2048,2048) };
    static int item_current = 3;
    ImGui::Combo("Resolution", &item_current, items, IM_ARRAYSIZE(items));
    if (ImGui::Button("Apply")) {
        renderer_ptr->setSceneFramebufferSize(rects[item_current]);
    }
    ImGui::End();

    if (renderer_ptr != nullptr) {
        renderer_ptr->setClearColor(Vector3(color.x, color.y, color.z));
    }
}

void drawMainScene(Entity entity, ImGuiComponent& _this) {
    if (renderer_ptr == nullptr) {
        return;
    }

    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    const GLTexture& sceneTexture = renderer_ptr->getSceneTexture();
    if (p_open) {
        ImGui::Begin("Scene View", &p_open, window_flags);
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImRect innerRect = window->InnerClipRect;

        ImVec2 viewprtSize = window->InnerClipRect.GetSize();
        ImGui::Image((void*)(intptr_t)(sceneTexture.id), viewprtSize);
        ImGui::End();
    }

}

class EditorApp : public Reborn::Application 
{
public:
    EditorApp() : Application(getWindowConfig()) {
        renderer_ptr = this->renderer.get();
        renderer->setSceneFramebufferSize(Vector2(1024, 1024));
        setupResourceManager();
        auto& entityManager = System::get().entityManager();

        Entity dockspaceEntity = entityManager.createEntity();
        entityManager.addComponent<ImGuiComponent>(dockspaceEntity, std::function(drawDockspace));

        Entity propertiesViewEntity = entityManager.createEntity();
        entityManager.addComponent<ImGuiComponent>(propertiesViewEntity, std::function(drawPropertyView));

        Entity sceneViewEntity = entityManager.createEntity();
        entityManager.addComponent<ImGuiComponent>(sceneViewEntity, std::function(drawMainScene));

        Entity triangleEntity;
        createTriangleEntity(triangleEntity);

        testMatrix();
    }

    ~EditorApp() {

    }
private:
    void setupResourceManager() {
        auto& resourceManager = System::get().resourceManager();
        resourceManager.setAssetsPath(ASSETS_PATH);
        TextResource* defaultTextResource = new TextResource("default text");
        resourceManager.addDefaultResource(defaultTextResource);
    }

    bool createTriangleEntity(Entity& triangleEntity) {
        auto& resourceManager = System::get().resourceManager();
        const TextResource* vertexShaderSource =
            resourceManager.getResourceOrCreate<TextResource>("shaders/simple_triangle/vertex.glsl");
        const TextResource* fragmentShaderSource =
            resourceManager.getResourceOrCreate<TextResource>("shaders/simple_triangle/fragment.glsl");

        if (vertexShaderSource == nullptr || fragmentShaderSource == nullptr) {
            LOG_ERROR << "failed to load shader source";
            return false;
        }

        GLSLProgram triangleProgram(vertexShaderSource->getText(), fragmentShaderSource->getText());
        renderer->create(triangleProgram);

        std::shared_ptr<float[]> vertices(new float[] {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
            });
        VertexBufferObject vbo(vertices, 9);
        std::vector<VertexAttribute> layout;
        layout.emplace_back(3, 3 * sizeof(float), GL_FALSE, GL_FLOAT);
        VertexArrayObject triangleVAO(vbo, layout);

        renderer->create(triangleVAO);

        auto& entityManager = System::get().entityManager();
        triangleEntity = entityManager.createEntity();
        entityManager.addComponent<Transform3DComponent>(triangleEntity);
        entityManager.addComponent<RenderComponent>(triangleEntity, triangleVAO, triangleProgram);
        return true;
    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}