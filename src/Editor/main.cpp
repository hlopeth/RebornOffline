#include "Reborn.h"
#include "Components/TestComponent.h"

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

class EditorApp : public Reborn::Application 
{
public:
    EditorApp(): Application(getWindowConfig()) {
        auto& entityManager = System::get().entityManager();

        std::vector<Entity> entities;
        entities.resize(50);

        for (int i = 0; i < 50; i++) {
            Entity entity = entityManager.createEntity();
            entityManager.addComponent<TestComponent>(entity);
            entities.push_back(entity);
        }

        for (auto entity : entities) {
            entityManager.removeEntity(entity);
        }
    }

    ~EditorApp() {

    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}