#include "Core.h"
#include "TextResource.h"
#include <fstream>

Reborn::TextResource::TextResource() : AbstractResource(0x23cedd45)
{
}

bool Reborn::TextResource::tryLoad(const std::string& path)
{
	std::ifstream infile;
	infile.open(path);
	if (!infile.is_open()) {
		LOG_ERROR << "TextResource::tryLoad failed to open file " << path;
		return false;
	}
	std::stringstream buffer;
	buffer << infile.rdbuf();
	text = buffer.str();
	loaded = true;
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
