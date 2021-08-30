#include "Reborn.h"

#include "Editors.h"
#include "CameraController.h"
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
    defaultConfig.fullscreen = false;

    return defaultConfig;
}

ImGuiID dockspace_id;
bool first_frame = true;
Entity mainEntity;

void drawDockspace(Entity cameraControllerEntity, ImGuiComponent& _this) {
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
                Application::get()->eventDispatcher().triggerEvent(Reborn::ApplicationShouldCloseEvent());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

void drawPropertyView(Entity cameraControllerEntity, ImGuiComponent& _this) {
    static ImVec4 color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", &p_open, window_flags);
    ImGui::ColorPicker4("Background", (float*)&color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

    auto& transform = Application::get()->entityManager().getComponent<Transform3DComponent>(mainEntity);
    transform3dEditor(transform);

    cameraEditor(Application::get()->renderer().getCamera());
    
    const char* items[] = { "128x128", "256x256", "512x512", "1024x1024", "2048x2048"};
    Vector2 rects[] = { Vector2(128,128), Vector2(256,256), Vector2(512,512), Vector2(1024,1024), Vector2(2048,2048) };
    static int item_current = 3;

    ImGui::Combo("Resolution", &item_current, items, IM_ARRAYSIZE(items));

    Renderer& renderer = Application::get()->renderer();

    if (ImGui::Button("Apply")) {
        renderer.setSceneFramebufferSize(rects[item_current]);
    }

    if (ImGui::Button("Reload resources")) {
        const std::string resource = "shaders/simple_triangle";
        bool result = Application::get()->resourceManager().reloadResource(resource);
    }
    ImGui::End();

    renderer.setClearColor(Vector3(color.x, color.y, color.z));
}

void drawMainScene(Entity cameraControllerEntity, ImGuiComponent& _this) {
    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    const GLTexture& sceneTexture = Application::get()->renderer().getSceneTexture();
    if (p_open) {
        ImGui::Begin("Scene View", &p_open, window_flags);
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImRect innerRect = window->InnerClipRect;

        ImVec2 viewprtSize = window->InnerClipRect.GetSize();
        viewprtSize.y -= 15;
        Application::get()->renderer().getCamera().setAspect(viewprtSize.x / viewprtSize.y);
        ImGui::Image((void*)(intptr_t)(sceneTexture.id), viewprtSize);
        ImGui::End();
    }

}

class EditorApp : public Reborn::Application 
{
public:
    EditorApp() : Application(getWindowConfig()) {
    }

    void Start() override {
        renderer().setSceneFramebufferSize(Vector2(1024, 1024));
        setupResourceManager();
        auto& entityMng = entityManager();

        Entity dockspaceEntity = entityMng.createEntity();
        entityMng.addComponent<ImGuiComponent>(dockspaceEntity, std::function(drawDockspace));

        Entity propertiesViewEntity = entityMng.createEntity();
        entityMng.addComponent<ImGuiComponent>(propertiesViewEntity, std::function(drawPropertyView));

        Entity sceneViewEntity = entityMng.createEntity();
        entityMng.addComponent<ImGuiComponent>(sceneViewEntity, std::function(drawMainScene));


        createCubeEntity(mainEntity);

        renderer().getCamera().setPosition(Vector3(0, 3, 3));

        cameraController.init(this);
    }

    ~EditorApp() {

    }
private:
    void setupResourceManager() {
        auto& resourceMng = resourceManager();
        resourceMng.setAssetsPath(ASSETS_PATH);
        TextResource* defaultTextResource = new TextResource("default text");
        resourceMng.addDefaultResource(defaultTextResource);
    }

    bool createTriangleEntity(Entity& triangleEntity) {
        const GLSLShaderResouce* shaderResource = resourceManager().getResourceOrCreate<GLSLShaderResouce>("shaders/simple_triangle");

        std::shared_ptr<float[]> vertices(new float[] {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
            });
        VertexBufferObject vbo(vertices, 9);
        std::vector<VertexAttribute> layout;
        layout.emplace_back(3, 3 * sizeof(float), GL_FALSE, GL_FLOAT);
        VertexArrayObject triangleVAO(vbo, layout);

        renderer().create(triangleVAO);

        triangleEntity = entityManager().createEntity();
        entityManager().addComponent<Transform3DComponent>(triangleEntity);
        //entityManager().getComponent<Transform3DComponent>(triangleEntity).position.z = -3;
        entityManager().addComponent<RenderComponent>(triangleEntity, triangleVAO, shaderResource->getProgram());
        return true;
    }

    bool createCubeEntity(Entity& cubeEntity) {
        const GLSLShaderResouce* shaderResource = resourceManager().getResourceOrCreate<GLSLShaderResouce>("shaders/simple_triangle");

        std::shared_ptr<float[]> vertices(new float[] {
            -1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f,  1.f, -1.f,
             1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f,
            -1.f, -1.f, -1.f,

            -1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
            -1.f,  1.f,  1.f,
            -1.f, -1.f,  1.f,

            -1.f,  1.f,  1.f,
            -1.f,  1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f, -1.f,  1.f,
            -1.f,  1.f,  1.f,

             1.f,  1.f,  1.f,
             1.f,  1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f,  1.f,
             1.f,  1.f,  1.f,

            -1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
            -1.f, -1.f,  1.f,
            -1.f, -1.f, -1.f,

            -1.f,  1.f, -1.f,
             1.f,  1.f, -1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
            -1.f,  1.f,  1.f,
            -1.f,  1.f, -1.f,
            });
        VertexBufferObject vbo(vertices, 3 * 6 * 6);
        std::vector<VertexAttribute> layout;
        layout.emplace_back(3, 3 * sizeof(float), GL_FALSE, GL_FLOAT);
        VertexArrayObject triangleVAO(vbo, layout);

        renderer().create(triangleVAO);

        cubeEntity = entityManager().createEntity();
        entityManager().addComponent<Transform3DComponent>(cubeEntity);
        //entityManager().getComponent<Transform3DComponent>(cubeEntity).position.z = -3;
        entityManager().addComponent<RenderComponent>(cubeEntity, triangleVAO, shaderResource->getProgram());
        return true;
    }

    CameraController cameraController;
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}