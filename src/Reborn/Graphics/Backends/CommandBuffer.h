#pragma once

namespace Reborn {
	class CommandBuffer {
	public:
		enum CommandType {
			INIT_BACKEND,
			CREATE_VERTEX_BUFFER,
			CREATE_INDEX_BUFFER,
		};

		CommandBuffer(size_t baseCapacity = 0);
		CommandBuffer& write(const void* data, size_t sizeInBytes);
		template<typename T>
		CommandBuffer& write(const T& in) {
			return write(reinterpret_cast<const char*>(&in), sizeof(T));
		};
		CommandBuffer& read(void* data, size_t sizeInBytes);
		template<typename T>
		CommandBuffer& read(T& out) {
			return read(reinterpret_cast<char*>(&out), sizeof(T));
		}
		bool empty();
		~CommandBuffer();
	private:
		void realloc(size_t newCapacity);
		char* buffer;
		size_t bufferCapacity;
		size_t writeInx;
		size_t readInx;
	};
}