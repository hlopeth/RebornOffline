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

void Reborn::ResourceManager::removeResource(const std::string& filename) {
	auto resourceSearchResult = filenameToData.find(filename);
	if (resourceSearchResult == filenameToData.end()) {
		return;
	}

	AbstractResource* resourceRef = resourceSearchResult->second;
	//не удаляем ресурс если он ссылается на дефолтный
	auto defaultResourceSearchResult = defaultResources.find(resourceRef->getType());
	if (defaultResourceSearchResult != defaultResources.end()) {
		return;
	}

	filenameToData.erase(resourceSearchResult);
	resourceRef->unload();
	delete resourceRef;
}


bool Reborn::ResourceManager::reloadResource(const std::string& filename)
{
	auto foundData = filenameToData.find(filename);
	if (foundData == filenameToData.end()) {
		LOG_ERROR << "ResourceManager::reloadResource: " << filename << " is not known to ResourceManager";
		return false;
	}
	else {
		foundData->second->unload();
		return foundData->second->tryLoad(getFullFilename(filename));
	}
}

std::string Reborn::ResourceManager::getFullFilename(const std::string& filename)
{
	return assetsPath + '/' + filename;
}

Reborn::ResourceManager::~ResourceManager() {
	for (auto it : filenameToData) {
		AbstractResource* resourceRef = it.second;
		//не удаляем ресурс если он ссылается на дефолтный
		auto defaultResourceSearchResult = defaultResources.find(resourceRef->getType());
		if (defaultResourceSearchResult != defaultResources.end()) {
			return;
		}

		resourceRef->unload();
		delete resourceRef;
	}

	for (auto it : defaultResources) {
		if (it.second->notLoaded()) {
			it.second->unload();
		}
		delete it.second;
	}
};