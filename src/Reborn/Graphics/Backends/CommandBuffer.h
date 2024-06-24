#pragma once

namespace Reborn {
	class CommandBuffer {
	public:
		enum class CommandType {
			INIT_BACKEND,
			CREATE_VERTEX_BUFFER,
			CREATE_INDEX_BUFFER,
			CREATE_VERTEX_ARRAY_OBJECT,
			CREATE_TEXTURE,
			CREATE_RENDERBUFFER,
			CREATE_FRAMEBUFFER,
			CREATE_SHADER_PROGRAM,
			ALLOCATE_TEXTURE,
			ALLOCATE_RENDERBUFFER,
			ATTACH_TEXTURE_TO_FRAMEBUFFER,
			ATTACH_RENDERBUFFER_TO_FRAMEBUFFER,
			SET_FRAMEBUFFER_DRAWBUFFERS,
			BIND_FRAMEBUFFER,
			BIND_TEXTURE,
			BIND_SHADER_PROGRAM,
			SET_NAMED_UNIFORM_VALUE,
			ACTIVATE_TEXTURE,
			COUNT
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