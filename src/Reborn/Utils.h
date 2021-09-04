#pragma once

namespace Reborn {
	template<class T>
	class RefCounter {
	public:
		RefCounter(T _data): data(_data), _refs(1) {}
		bool hasRefs() const {
			return _refs > 0;
		}
		void addRef() {
			_refs++;
		}
		void removeRef() {
			_refs--;
		}
		uint32_t refs() const {
			return _refs;
		}
		T data;
	private:
		int32_t _refs = 0;
	};
}