#pragma once
#include "Core.h"
#include <bitset>
#include <limits>
#include "Backends/RenderBackendTypes.h"

namespace Reborn {
	const Handler InvalidHandle = UINT_MAX;

	template<std::size_t MaxHandlers>
	class HandleAllocator {
	public:
		HandleAllocator() {
			freeHandles.reserve(MaxHandlers / 10);
		}
		Handler allocate() {
			if (!freeHandles.empty()) {
				Handler freeID = freeHandles.back();
				freeHandles.pop_back();
				allocatedHandles.set(freeID, true);
				return freeID;
			}
			else {
				size_t count = allocatedHandles.count();
				if (count == allocatedHandles.size()) {
					LOG_ERROR << "HandleAllocator.allocate: Unable to allocate new Handle";
					return InvalidHandle;
				}
				allocatedHandles.set(count, true);
				return count;
			}
		};
		void free(Handler handle) {
			if (allocatedHandles.test(handle) == false) {
				LOG_WARN << "HandleAllocator.free: Expected handle " << handle << " to be taken? but it's free instead";
				return;
			}
			allocatedHandles.flip(handle);
			freeHandles.push_back(handle);
		};
	private:
		std::vector<Handler> freeHandles;
		std::bitset<MaxHandlers> allocatedHandles;
	};
}