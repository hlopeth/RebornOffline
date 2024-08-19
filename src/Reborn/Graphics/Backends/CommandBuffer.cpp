#include "CommandBuffer.h"
#include "CommandBuffer.h"
#include "CommandBuffer.h"
#include "CommandBuffer.h"
#include "Core.h"
#include "CommandBuffer.h"

Reborn::CommandBuffer::CommandBuffer(size_t baseCapacity) :
	buffer(nullptr),
	bufferCapacity(0),
	writeInx(0),
	readInx(0)
{
	realloc(baseCapacity);
}

Reborn::CommandBuffer& Reborn::CommandBuffer::write(const void* data, size_t sizeInBytes) {
	if (writeInx + sizeInBytes > bufferCapacity) {
		size_t newCapacity = max(bufferCapacity * 2, sizeInBytes);
		realloc(newCapacity);
	}

	memcpy(&buffer[writeInx], data, sizeInBytes);
	writeInx += sizeInBytes;

	return *this;
}


Reborn::CommandBuffer& Reborn::CommandBuffer::writeString(const std::string inStr) {
	write(inStr.length());
	write(inStr.data(), inStr.length());
	return *this;
}

Reborn::CommandBuffer& Reborn::CommandBuffer::read(void* data, size_t sizeInBytes) {
	if (readInx + sizeInBytes > writeInx) {
		LOG_ERROR << "CommandBuffer: trying to read when not enouth data to be read";
		return *this;
	}
	memcpy(data, &buffer[readInx], sizeInBytes);
	readInx += sizeInBytes;
	return *this;
}

Reborn::CommandBuffer& Reborn::CommandBuffer::readString(std::string& outStr) {
	size_t outStrLength;
	read(outStrLength);
	outStr.resize(outStrLength, '%');
	read(outStr.data(), outStrLength);
	return *this;
}

bool Reborn::CommandBuffer::empty() {
	return readInx >= writeInx;
}

Reborn::CommandBuffer::~CommandBuffer() {
	delete[] buffer;
}

void Reborn::CommandBuffer::realloc(size_t newCapacity) {
	char* newBuffer = new char[newCapacity];
	if (buffer != nullptr) {
		memcpy(newBuffer, buffer, bufferCapacity);
		delete[] buffer;
	}

	buffer = newBuffer;
	bufferCapacity = newCapacity;
}
