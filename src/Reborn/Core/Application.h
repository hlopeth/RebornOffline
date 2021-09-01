#pragma once
#include "Window.h"
#include "Graphics/Renderer.h"
#include <ECS/EntitySystem.h>
#include <Event/EventDispatcher.h>
#include <Resources/ResourceManager.h>
#include <ECS/EntityManager.h>

namespace Reborn {
	class Application
	{
	public:
		static bool internalInit(Reborn::Application*(*createApplication)());
		static Application* get();
		static void Destroy();
		virtual void Start() = 0;
		void Run();
		void Close();
		virtual ~Application();
		void onApplicationClose(const IEvent& evt);

		EventDispatcher& eventDispatcher();
		ResourceManager& resourceManager();
		Renderer& renderer();
		EntityManager& entityManager();
	protected:
		Application(WindowConfiguration windowConfig);
		std::unique_ptr<Window> window;
		EntitySystem* imGuiSystem = nullptr;
		EntitySystem* rendererSystem = nullptr;
		EntitySystem* tickSystem = nullptr;
	private: 
		static Application* appInstance;

		void PoolEvents();
		bool shouldClose = false; 
		t_EventHandler closeHandler;

		std::unique_ptr<Renderer> _renderer;
		EventDispatcher _eventDispatcher;
		ResourceManager _resourceManager;
		EntityManager _entityManager;
	};
}