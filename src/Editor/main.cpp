#include <iostream>
#include "Reborn.h"

class EditorApp : public Reborn::Application 
{
public:
    EditorApp() {

    }

    ~EditorApp() {

    }
};

Reborn::Application* CreateApplication() {
    return new EditorApp();
}