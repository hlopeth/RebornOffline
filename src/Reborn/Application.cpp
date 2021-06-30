#include "Core.h"
#include "Application.h"
#include <SDL.h>
#include "Event/KeyPressedEvent.h"
#include "Event/ApplicationShouldCloseEvent.h"
#include "SDLUtils.h"

SDL_Event event;
Reborn::t_EventHandler keyPressedHandler = [](const Reborn::IEvent& evt) {  
	auto keyEvent = static_cast<const Reborn::KeyPressedEvent&>(evt);
	if (keyEvent.key == KeyCode::key_escape) {
		Reborn::System::get().eventDispatcher().triggerEvent(Reborn::ApplicationShouldCloseEvent());
	}
	else {
		LOG_DEBUG << (char)keyEvent.key;
	}
};

void test(const Reborn::ApplicationShouldCloseEvent& evt) {
	LOG_DEBUG << "test handler";
}

Reborn::Application::Application(WindowConfiguration windowConfig):
	window(Window::CreateSDLWindow(windowConfig)),
	closeHandler(std::bind(&Application::onApplicationClose, this, std::placeholders::_1))
{
	if (!window) {
		shouldClose = true;
	}

	System::get().eventDispatcher().subscribe(ApplicationShouldCloseEvent::TYPE(), &closeHandler);
	System::get().eventDispatcher().subscribe(KeyPressedEvent::TYPE(), &keyPressedHandler);
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
	System::get().eventDispatcher().unsubscribe(ApplicationShouldCloseEvent::TYPE(), &closeHandler);
}

void Reborn::Application::PoolEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT: 
			System::get().eventDispatcher().triggerEvent(ApplicationShouldCloseEvent());
			break;
		case SDL_KEYDOWN:
			{
			KeyCode keyCode = ToRebornKeyCode(event.key.keysym.sym);
			System::get().eventDispatcher().triggerEvent(KeyPressedEvent(keyCode));
			}
			break;
		case SDL_KEYUP:

		default:
			break;
		}
	}
}

void Reborn::Application::onApplicationClose(const IEvent& evt)
{
	Close();
}