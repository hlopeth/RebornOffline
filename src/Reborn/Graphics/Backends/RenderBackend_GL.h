#pragma once
#include "RenderBackend.h"
#include "RenderBackendTypes.h"

namespace Reborn {
	class RenderBackend_GL : public RenderBackend {
	public:
		RenderBackend_GL(SDL_GLContext& context);
		~RenderBackend_GL();
		virtual void processComandBuffer();
		virtual const RenderContext_Handler getContext();
	private:
		void init();
		SDL_GLContext context;

	};
}