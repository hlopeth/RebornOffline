#pragma once
#include "RenderBackendTypes.h"
#include "CommandBuffer.h"

namespace Reborn {
	class RenderBackend
	{
	public:
		RenderBackend(BackendType _backendType) : backendType(_backendType) {};
		CommandBuffer& commandBuffer() { return _commandBuffer; }
		virtual void processComandBuffer() = 0;
		virtual const RenderContext_Handler getContext() = 0;
		const BackendType backendType;
	protected:
		CommandBuffer _commandBuffer;
	};
}