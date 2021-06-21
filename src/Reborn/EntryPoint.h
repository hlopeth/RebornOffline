#pragma once
#include "System.h"
#include "Application.h"

extern Reborn::Application* CreateApplication();

int main(int argc, char* argv[]) {
	if (Reborn::System::get().Init() != 0) {
		return 0;
	}

	Reborn::Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}