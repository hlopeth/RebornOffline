#include "Core.h"
#include "ResourceManager.h"

void Reborn::ResourceManager::setAssetsPath(const char* path)
{
	assetsPath = path;
}

template<typename ResourceType>
Reborn::AbstractResource* getResource(const std::string& filename)
{
	auto result = filenameToData.find(filename);
	if (result == filenameToData.end()) {
		ResourceType* resource
	    bool result = T::load();
		filenameToData.insert()
	}


}
