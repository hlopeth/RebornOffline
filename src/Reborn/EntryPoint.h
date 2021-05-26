#pragma once
#include "Core.h"
#include "Application.h"

extern Reborn::Application* CreateApplication();

int main(int argc, char** argv) {
	if (Reborn::Init() != 0) {
		return 0;
	}

	Reborn::Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}