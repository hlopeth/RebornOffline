#include "Reborn.h"

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
    }

    ~EditorApp() {

    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}