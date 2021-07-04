#pragma once

namespace Reborn
{
	template<typename T, size_t Type>
	class Component
	{
	public:
		static constexpr size_t type = Type;
	};
}