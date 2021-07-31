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
	//�� ������� ������ ���� �� ��������� �� ���������
	auto defaultResourceSearchResult = defaultResources.find(resourceRef->getType());
	if (defaultResourceSearchResult != defaultResources.end()) {
		return;
	}

	filenameToData.erase(resourceSearchResult);
	resourceRef->unload();
	delete resourceRef;
};

Reborn::ResourceManager::~ResourceManager() {
	for (auto it : filenameToData) {
		AbstractResource* resourceRef = it.second;
		//�� ������� ������ ���� �� ��������� �� ���������
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