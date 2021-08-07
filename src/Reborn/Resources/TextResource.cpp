#include "Core.h"
#include "TextResource.h"

Reborn::TextResource::TextResource() : AbstractResource(0x23cedd45)
{
}

Reborn::TextResource::TextResource(std::string _text) : AbstractResource(0x23cedd45), text(_text)
{
}

bool Reborn::TextResource::tryLoad(const std::string& path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.is_open()) {
		LOG_ERROR << "TextResource::tryLoad failed to open file " << path;
		inFile.close();
		return false;
	}
	std::stringstream buffer;
	buffer << inFile.rdbuf();
	text = buffer.str();
	loaded = true;
	inFile.close();
	return true;
}

bool Reborn::TextResource::unload()
{
	text = "";
	loaded = false;
	return true;
}

const std::string& Reborn::TextResource::getText() const
{
	return text;
}
