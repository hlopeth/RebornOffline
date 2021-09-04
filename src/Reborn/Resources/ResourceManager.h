#pragma once
#include "AbstractResource.h"
#include "fstream"

namespace Reborn {
	class ResourceManager {
	public:
		ResourceManager() = default;
		~ResourceManager();
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
						newResource = reinterpret_cast<ResourceType*>(defaultResourceSearchResult->second);
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

		//��������� ������ �� ���������. 
		//���� ������ �� ��������� � ���� ������ ��� ���� �� �� ����� �����������.
		//filename - ��� ������� ������������ assetsPath.
		template<typename ResourceType>
		bool tryAddDefaultResource(const std::string& filename) {
			ResourceType* newDefaultResource = new ResourceType();

			const std::string fullFilename = getFullFilename(filename);
			bool sucsess = newDefaultResource->tryLoad(fullFilename);
			if (!sucsess) {
				delete newDefaultResource;
				return false;
			}
			else {
				addDefaultResource<ResourceType>(newDefaultResource);
				return true;
			}
		}

		template<typename ResourceType>
		void addDefaultResource(ResourceType* newDefaultResource) {
			defaultResources.insert({ newDefaultResource->getType(), reinterpret_cast<AbstractResource*>(newDefaultResource) });
		}

		void removeResource(const std::string& filename);

		bool reloadResource(const std::string& filename);

		const std::unordered_map<std::string, AbstractResource*>& getAllResources() const;

	private:
		std::string getFullFilename(const std::string& filename);
		std::string assetsPath;
		std::unordered_map<std::string, AbstractResource*> filenameToData;
		std::unordered_map<ResourceTypeID, AbstractResource*> defaultResources;
	};
}