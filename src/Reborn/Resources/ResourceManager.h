#pragma once
#include "AbstractResource.h"
#include "fstream"

namespace Reborn {
	class ResourceManager {
	public:
		ResourceManager() = default;
		~ResourceManager() {
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
		//������������� ���������� ���� �� ����� � ���������.
		void setAssetsPath(const char* path);
		//���� ������ ��� �� ��� �������� �������� ������.
		//filename - ��� ������� ������������ assetsPath.
		template<typename ResourceType>
		const ResourceType* getResourceOrCreate(const std::string& filename)
		{
			auto resourceSearchResult = filenameToData.find(filename);
			AbstractResource* resourceRef = nullptr;

			//����� ������ � ����� ��� ��������������
			if (resourceSearchResult == filenameToData.end()) {
				ResourceType* newResource = new ResourceType();
				
				const std::string fullFilename = assetsPath + '/' + filename;
				bool sucsess = newResource->tryLoad(fullFilename);
				//��� ��������� �������� ������� ������ � �������� �� ������ �� ���������, ���� ����� �������
				if (!sucsess) {
					const ResourceTypeID resType = newResource->getType();
					delete newResource;

					auto defaultResourceSearchResult = defaultResources.find(resType);
					if (defaultResourceSearchResult != defaultResources.end()) {
						newResource = reinterpret_cast<ResourceType*>(&defaultResourceSearchResult->second);
					}
					else {
						newResource = nullptr;
					}
				}

				if (newResource != nullptr) {
					filenameToData.insert({ filename, newResource });
					resourceRef = newResource;
				}
			}
			else {
				resourceRef = resourceSearchResult->second;
			}

			return reinterpret_cast<ResourceType*>(resourceRef);
		}

		void removeResource(const std::string& filename) {
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
	private:
		std::string assetsPath;
		std::unordered_map<std::string, AbstractResource*> filenameToData;
		std::unordered_map<ResourceTypeID, AbstractResource*> defaultResources;
	};
}