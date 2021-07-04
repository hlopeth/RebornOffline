#include "Reborn.h"
#include "Components/TestComponent.h"

using namespace Reborn;

Reborn::WindowConfiguration defaultConfig = {
    "Editor",
    100,
    100,
    600,
    500,
};

class EditorApp : public Reborn::Application 
{
public:
    EditorApp(): Application(defaultConfig) {
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