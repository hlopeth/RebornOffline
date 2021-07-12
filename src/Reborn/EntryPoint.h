#pragma once
#include "Core/System.h"
#include "Core/Application.h"
#include "Log.h"

INITIALIZE_EASYLOGGINGPP

extern Reborn::Application* CreateApplication();

void configureLogger()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Global, el::ConfigurationType::Format, "[%datetime{%h:%m:%s,%g}] %level : %msg");
	defaultConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "true");
	el::Loggers::reconfigureLogger("default", defaultConf);
	el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
}

int main(int argc, char* argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	configureLogger();

	LOG_INFO << "Application started";
	if (Reborn::System::get().Init() != 0) {
		return 0;
	}

	Reborn::Application* app = CreateApplication();
	app->Run();
	delete app;

	LOG_INFO << "Application finished";
	return 0;
}