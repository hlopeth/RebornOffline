#include "Reborn.h"

#include "Editors.h"
#include "CameraController.h"
#include "TestVector.h"
#include "TestMatrix.h"
#include "ResourceView.h"


using namespace Reborn;

Reborn::WindowConfiguration getWindowConfig() {
    Reborn::WindowConfiguration defaultConfig = { "Editor" };
    defaultConfig.x = 100;
    defaultConfig.y = 100;
    defaultConfig.width = 1000;
    defaultConfig.height = 800;
    defaultConfig.resizable = true;
    defaultConfig.fullscreen = false;

    return defaultConfig;
}

ImGuiID dockspace_id;
bool first_frame = true;
Entity mainEntity = NoEntity;

std::shared_ptr<Material> lowPolyMaterial;

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
            if (ImGui::MenuItem("Resources", "", false)) {
                showResourceView = true;
            }
            if (ImGui::MenuItem("Exit", "", false))
            {
                Application::get()->eventDispatcher().triggerEvent(Reborn::ApplicationShouldCloseEvent());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End(); 
    drawResourceView();
}

void drawPropertyView(Entity cameraControllerEntity, ImGuiComponent& _this) {
    auto& entityManager = Application::get()->entityManager();
    auto& resourceManager = Application::get()->resourceManager();
    if (mainEntity == NoEntity) {
        return;
    }
    Renderer& renderer = Application::get()->renderer();
    static ImVec4 lightColor = ImVec4(.5f, .5f, .5f, 1.0f);
    static float lightStr = 1.0;
    static ImVec4 ambientColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    bool p_open = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", &p_open, window_flags);
    ImGui::ColorPicker4("Light color", (float*)&lightColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
    ImGui::SliderFloat("Light strength", &lightStr, 0.0, 1.0, "% .01f");
    ImGui::ColorPicker4("Ambient color", (float*)&ambientColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

    auto& transform = entityManager.getComponent<Transform3DComponent>(mainEntity);
    transform3dEditor(transform);

    cameraEditor(Application::get()->renderer().getCamera());
    
    const char* model_items[] = { "rat", "deer", "cat", "wolf", "mill", "forest"};
    std::string model_paths[] = { 
        "models/lowpolyrat/rat.fbx",
        "models/lowpolydeer/deer.fbx",
        "models/lowpolycat/cat.fbx",
        "models/lowpolywolf/wolf.fbx",
        "models/Low_Poly_Low_Poly_Mill_obj/low-poly-mill.obj",
        "models/lowpoly_forest/ENFOR_EEVEE.obj",
    };
    static int model_item_current = 3;
    if (ImGui::Combo("Model", &model_item_current, model_items, IM_ARRAYSIZE(model_items))) {
        Transform transformCopy = entityManager.getComponent<Transform3DComponent>(mainEntity).getTransform();
        entityManager.removeEntity(mainEntity);
        mainEntity = NoEntity;
        const GLSLShaderResouce* shaderResource = resourceManager.getResourceOrCreate<GLSLShaderResouce>("shaders/lowpoly");
        
        const std::string& filename = model_paths[model_item_current];
        auto* modelResource = resourceManager.getResourceOrCreate<ModelResource>(filename);
        createModelEntity(mainEntity, modelResource->getModel());
        entityManager.getComponent<Transform3DComponent>(mainEntity).setTransform(transformCopy);
    }
    ImGui::ColorPicker4("Outline color", (float*)&renderer.outlineColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

    static Vector4 mainMaterialColor = Vector4(1.f, 1.f, 1.f, 1.f);

    ImGui::End();

    //renderer.setClearColor(Vector3(color.x, color.y, color.z));
    renderer.lightColor = Vector3(lightColor.x, lightColor.y, lightColor.z);
    renderer.ambientColor = Vector3(ambientColor.x, ambientColor.y, ambientColor.z);
    renderer.lightStr = lightStr;
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
        Application::get()->renderer().setSceneFramebufferSize(Vector2(viewprtSize.x, viewprtSize.y));
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

        const GLSLShaderResouce* shaderResource = resourceManager().getResourceOrCreate<GLSLShaderResouce>("shaders/lowpoly");
        lowPolyMaterial = std::make_shared<Material>(shaderResource->getProgram());
        const ModelResource* modelResource = resourceManager().getResourceOrCreate<ModelResource>("models/lowpolywolf/wolf.fbx");


        createModelEntity(mainEntity, modelResource->getModel());
        entityManager().getComponent<Transform3DComponent>(mainEntity).setScale(Vector3(0.02));
        entityManager().getComponent<Transform3DComponent>(mainEntity).setRotation(Vector3(-PI/2, 0, 0));

        renderer().getCamera().setPosition(Vector3(5, 5, -8));

        cameraController.init(this);
    }

    ~EditorApp() {
        entityManager().removeEntity(mainEntity);
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
        static Material material(shaderResource->getProgram());

        const Vector3 vertices[3] = {
            Vector3(-0.5f, -0.5f, 0.0f), // left  
            Vector3(0.5f, -0.5f, 0.0f), // right 
            Vector3(0.0f,  0.5f, 0.0f)  // top   
        };

        const uint32_t indeces[] = { 0, 1 ,2 };
        Mesh triangleMesh(3, indeces, 3, vertices);


        triangleEntity = entityManager().createEntity();
        entityManager().addComponent<Transform3DComponent>(triangleEntity);
        entityManager().addComponent<RenderComponent>(triangleEntity, std::move(triangleMesh), material);
        return true;
    }

    bool createCubeEntity(Entity& cubeEntity) {
        const GLSLShaderResouce* shaderResource = resourceManager().getResourceOrCreate<GLSLShaderResouce>("shaders/simple_triangle");
        static Material material(shaderResource->getProgram());

        const Vector3 vertices[] = {
            Vector3(-1.f, -1.f, -1.f),
            Vector3(1.f, -1.f, -1.f),
            Vector3(1.f,  1.f, -1.f),
            Vector3(1.f,  1.f, -1.f),
            Vector3(-1.f,  1.f, -1.f),
            Vector3(-1.f, -1.f, -1.f),

            Vector3(-1.f, -1.f,  1.f),
            Vector3(1.f, -1.f,  1.f),
            Vector3(1.f,  1.f,  1.f),
            Vector3(1.f,  1.f,  1.f),
            Vector3(-1.f,  1.f,  1.f),
            Vector3(-1.f, -1.f,  1.f),

            Vector3(-1.f,  1.f,  1.f),
            Vector3(-1.f,  1.f, -1.f),
            Vector3(-1.f, -1.f, -1.f),
            Vector3(-1.f, -1.f, -1.f),
            Vector3(-1.f, -1.f,  1.f),
            Vector3(-1.f,  1.f,  1.f),

            Vector3(1.f,  1.f,  1.f),
            Vector3(1.f,  1.f, -1.f),
            Vector3(1.f, -1.f, -1.f),
            Vector3(1.f, -1.f, -1.f),
            Vector3(1.f, -1.f,  1.f),
            Vector3(1.f,  1.f,  1.f),

            Vector3(-1.f, -1.f, -1.f),
            Vector3(1.f, -1.f, -1.f),
            Vector3(1.f, -1.f,  1.f),
            Vector3(1.f, -1.f,  1.f),
            Vector3(-1.f, -1.f,  1.f),
            Vector3(-1.f, -1.f, -1.f),

            Vector3(-1.f,  1.f, -1.f),
            Vector3(1.f,  1.f, -1.f),
            Vector3(1.f,  1.f,  1.f),
            Vector3(1.f,  1.f,  1.f),
            Vector3(-1.f,  1.f,  1.f),
            Vector3(-1.f,  1.f, -1.f)
        };

        const uint32_t indices[] = {
            0,1,2,
            3,4,5,
            6,7,8,
            9,10,11,
            12,13,14,
            15,16,17,
            18,19,20,
            21,22,23,
            24,25,26,
            27,28,29,
            30,31,32,
            33,34,35
        };

        Mesh cubeMesh(36, indices, 36, vertices);

        cubeEntity = entityManager().createEntity();
        entityManager().addComponent<Transform3DComponent>(cubeEntity);
        entityManager().addComponent<RenderComponent>(cubeEntity, std::move(cubeMesh), material);
        return true;
    }

    CameraController cameraController;
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}