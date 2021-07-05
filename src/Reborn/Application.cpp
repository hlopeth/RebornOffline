#include "Core.h"
#include "Application.h"
#include <SDL.h>
#include "Event/KeyPressedEvent.h"
#include "Event/ApplicationShouldCloseEvent.h"
#include "SDLUtils.h"

#include <Components/TestComponent.h>
#include <Components/Transform3DComponent.h>
#include <Components/ImGuiComponent.h>
#include <Systems/TestSystem.h>
#include <Systems/ImGuiSystem.h>

//Reborn::ImGuiSystem<Reborn::System::maxComponents, Reborn::System::maxEntitySystems>* imguiSystem;

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
	window(nullptr),
	renderer(nullptr),
	closeHandler(std::bind(&Application::onApplicationClose, this, std::placeholders::_1))
{
	window = std::unique_ptr<Window>(Window::CreateSDLWindow(windowConfig));

	if (!window) {
		shouldClose = true;
	}
	else {
		renderer = std::make_unique<Renderer>(static_cast<Window&>(*window));
	}
	auto& system = System::get();

	system.entityManager().registerComponent<TestComponent>();
	system.entityManager().registerComponent<Transform3DComponent>();
	system.entityManager().registerComponent<ImGuiComponent>();
	auto testSystem = system.entityManager().createSystem<TestSystem<System::maxComponents, System::maxEntitySystems>>();
	imGuiSystem = system.entityManager().createSystem<ImGuiSystem<System::maxComponents, System::maxEntitySystems>>();

	system.eventDispatcher().subscribe(ApplicationShouldCloseEvent::TYPE(), &closeHandler);
	system.eventDispatcher().subscribe(KeyPressedEvent::TYPE(), &keyPressedHandler);
}

void Reborn::Application::Run()
{
	if (!window) {
		return;
	}

	while (!shouldClose)
	{
		PoolEvents();		

		static_cast<ImGuiSystem<System::maxComponents, System::maxEntitySystems>*>(imGuiSystem)->process();

		window->Update();
		renderer->draw();
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