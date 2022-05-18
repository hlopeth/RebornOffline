#include "Core.h"
#include "Application.h"
#include <SDL.h>
#include "Event/KeyPressedEvent.h"
#include "Event/MouseEvents.h"
#include "Event/ApplicationShouldCloseEvent.h"
#include "SDLUtils.h"

#include <Systems/TestSystem.h>
#include <Systems/ImGuiSystem.h>
#include <Systems/UpdateTransformSystem.h>
#include <Systems/RenderSystem.h>
#include <Systems/TickSystem.h>

#include <Resources/ShaderResource.h>
SDL_Event evt;

#ifdef REBORN_OPENGL
#include <Resources/GLSLShaderResource.h>

std::string defaultVertex =
#include <Graphics/shaders/lowpoly/vertex.glsl>
;

std::string defaultFragment =
#include <Graphics/shaders/lowpoly/fragment.glsl>
;
#endif // REBORN_OPENGL

Reborn::Application* Reborn::Application::appInstance = nullptr;

void test(const Reborn::ApplicationShouldCloseEvent& evt) {
	LOG_DEBUG << "test handler";
}

Reborn::Application::Application(WindowConfiguration windowConfig):
	window(nullptr),
	_renderer(nullptr),
	closeHandler(std::bind(&Application::onApplicationClose, this, std::placeholders::_1))
{
	window = std::unique_ptr<Window>(Window::CreateSDLWindow(windowConfig));

	if (!window) {
		shouldClose = true;
	}
	else {
#ifdef REBORN_OPENGL
		_renderer = std::make_unique<GLRenderer>(static_cast<Window&>(*window));
#else
		_renderer = std::make_unique<Renderer>(static_cast<Window&>(*window));
#endif // REBORN_OPENGL

	}

	//init imgui
	_imguiManager.init(_renderer.get(), window.get());

	_entityManager.registerComponent<TestComponent>();
	_entityManager.registerComponent<Transform3DComponent>();
	_entityManager.registerComponent<ImGuiComponent>();
	_entityManager.registerComponent<RenderComponent>();
	_entityManager.registerComponent<TickComponent>();
	auto testSystem = _entityManager.createSystem<TestSystem>();
	imGuiSystem = _entityManager.createSystem<ImGuiSystem>();
	updateTransformSystem = _entityManager.createSystem<UpdateTransformSystem>(_entityManager);
	rendererSystem = _entityManager.createSystem<RenderSystem>(_entityManager);
	tickSystem = _entityManager.createSystem<TickSystem>();

	_eventDispatcher.subscribe(ApplicationShouldCloseEvent::TYPE(), &closeHandler);

	//Default resources
#ifdef REBORN_OPENGL
	GLRenderer* glRenderer = static_cast<GLRenderer*>(_renderer.get());
	Reborn::GLShaderProgram defaultProgram = glRenderer->create(defaultVertex, defaultFragment);
	Reborn::ShaderResouce* defaultShaderResource = new Reborn::ShaderResouce(defaultProgram);
	_resourceManager.addDefaultResource<Reborn::ShaderResouce>(defaultShaderResource);
#endif // REBORN_OPENGL
}

bool Reborn::Application::internalInit(Reborn::Application* (createApplication)())
{
	Uint32 sdlInitFlags = SDL_INIT_VIDEO;
	if (SDL_Init(sdlInitFlags) != 0) {
		LOG_ERROR << "Error while sdl init. \n" << SDL_GetError();
		return false;
	}
	appInstance = createApplication();
	if (appInstance == nullptr) {
		LOG_FATAL << "createApplication returned nullptr";
		return false;
	}

	return true;
}

Reborn::Application* Reborn::Application::get()
{
	return appInstance;
}

void Reborn::Application::Destroy()
{
	delete appInstance;
	appInstance = nullptr;
}

void Reborn::Application::Run()
{
	if (!window) {
		return;
	}

	while (!shouldClose)
	{
		static_cast<UpdateTransformSystem*>(updateTransformSystem)->update();		
		PoolEvents();		

		static_cast<TickSystem*>(tickSystem)->update();
		static_cast<ImGuiSystem*>(imGuiSystem)->process(window->getSDLWindow());

		window->Update();

#if REBORN_OPENGL
		GLRenderer& glRenderer = static_cast<GLRenderer&>(*_renderer);
		glRenderer.beginFrame();
#endif
		static_cast<RenderSystem*>(rendererSystem)->process(*_renderer);
#if REBORN_OPENGL
		glRenderer.endFrame(_imguiManager);
#endif
	}

}

void Reborn::Application::Close()
{
	shouldClose = true;
}

Reborn::Application::~Application()
{
	_imguiManager.destroy();
	_eventDispatcher.unsubscribe(ApplicationShouldCloseEvent::TYPE(), &closeHandler);
}

void Reborn::Application::PoolEvents()
{
	while (SDL_PollEvent(&evt) != 0)
	{
		_imguiManager.processEvent(evt);
		switch (evt.type)
		{
		case SDL_QUIT: 
			_eventDispatcher.triggerEvent(ApplicationShouldCloseEvent());
			break;
		case SDL_KEYDOWN:
			{
			KeyCode keyCode = ToRebornKeyCode(evt.key.keysym.sym);
			_eventDispatcher.triggerEvent(KeyPressedEvent(keyCode));
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			MouseButtonCode buttonCode = ToRebornMoseButtonCode(evt.button.button);
			_eventDispatcher.triggerEvent(MouseButtonPressedEvent(buttonCode));
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			MouseButtonCode buttonCode = ToRebornMoseButtonCode(evt.button.button);
			_eventDispatcher.triggerEvent(MouseButtonReleasedEvent(buttonCode));
		}
		break;
		case SDL_MOUSEMOTION:
		{
			auto motion = evt.motion;
			_eventDispatcher.triggerEvent(MouseMotionEvent(motion.x, motion.y, motion.xrel, motion.yrel));
		}
		break;
		case SDL_MOUSEWHEEL:
		{
			_eventDispatcher.triggerEvent(MouseWheelEvent(evt.wheel.x, evt.wheel.y, evt.wheel.direction));
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

Reborn::EventDispatcher& Reborn::Application::eventDispatcher()
{
	return _eventDispatcher;
}

Reborn::ResourceManager& Reborn::Application::resourceManager()
{
	return _resourceManager;
}

Reborn::Renderer& Reborn::Application::renderer() {
	return *_renderer;
}


Reborn::EntityManager& Reborn::Application::entityManager()
{
	return _entityManager;
}

Reborn::ImGuiManager& Reborn::Application::imGuiManaget()
{
	return _imguiManager;
}