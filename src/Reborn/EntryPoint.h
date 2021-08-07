#pragma once
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

	if (!Reborn::Application::internalInit(CreateApplication)) {
		LOG_FATAL << "Failed to init basic application";
		return 0;
	}

	LOG_INFO << "Application started";	

	Reborn::Application* app = Reborn::Application::get();

	app->Start();
	app->Run();
	app->Destroy();

	LOG_INFO << "Application finished";
	return 0;
}