#pragma once
#include <cstdint>
#define REBORN_COMPONENTS_COUNT 100
#define REBORN_SYSTEM_COUNT 10

namespace Reborn 
{
	typedef uint32_t Entity;

	typedef uint32_t Index;
	static constexpr auto InvalidIndex = UINT32_MAX;
	static constexpr Entity NoEntity = -1;
}