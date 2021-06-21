#pragma once
#include "System.h"
#include "Application.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

extern Reborn::Application* CreateApplication();

void configureLogger()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Global, el::ConfigurationType::Format, "[%datetime{%h:%m:%s,%g}] %level : %msg");
	defaultConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "true");
	el::Loggers::reconfigureLogger("default", defaultConf);
}

int main(int argc, char* argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	configureLogger();

	LOG(DEBUG) << "START";
	if (Reborn::System::get().Init() != 0) {
		return 0;
	}

	LOG(DEBUG) << "INIT";
	Reborn::Application* app = CreateApplication();
	LOG(DEBUG) << "CreateApplication";
	app->Run();
	delete app;

	LOG(DEBUG) << "STOP";
	return 0;
}