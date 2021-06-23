#include "Application.h"
#include <SDL.h>
#include "Log.h"

SDL_Event event;
Reborn::t_EventHandler lambdaHandler;

void test(const Reborn::ApplicationCloseEvent& evt) {
	LOG_DEBUG << "test handler";
}

Reborn::Application::Application(WindowConfiguration windowConfig):
	window(Window::CreateSDLWindow(windowConfig)),
	closeHandler(std::bind(&Application::onApplicationClose, this, std::placeholders::_1))
{
	if (!window) {
		shouldClose = true;
	}

	lambdaHandler = [](const IEvent& evt) { LOG_DEBUG << "lambda handler"; };

	System::get().eventDispatcher().subscribe(ApplicationCloseEvent::TYPE(), &closeHandler);
	System::get().eventDispatcher().subscribe(ApplicationCloseEvent::TYPE(), &lambdaHandler);
}

void Reborn::Application::Run()
{
	if (!window) {
		return;
	}

	while (!shouldClose)
	{
		PoolEvents();		
		window->Update();
	}

}

void Reborn::Application::Close()
{
	shouldClose = true;
}

Reborn::Application::~Application()
{
	System::get().eventDispatcher().unsubscribe(ApplicationCloseEvent::TYPE(), &closeHandler);
}

void Reborn::Application::PoolEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT: 
			System::get().eventDispatcher().triggerEvent(ApplicationCloseEvent());
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
			System::get().eventDispatcher().triggerEvent(ApplicationCloseEvent());
			}
			break;
		default:
			break;
		}
	}
}

void Reborn::Application::onApplicationClose(const IEvent& evt)
{
	LOG_DEBUG << "member handler";
	shouldClose = true;
}