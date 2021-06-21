#include "EventHandlerBase.h"

Reborn::EventHandlerBase::~EventHandlerBase()
{
}

void Reborn::EventHandlerBase::invoke(const Reborn::IEvent& event)
{
	call(event);
}

void Reborn::EventHandlerBase::call(const Reborn::IEvent& event)
{
	intCall(event);
}
