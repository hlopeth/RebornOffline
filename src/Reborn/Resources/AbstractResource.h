#pragma once

namespace Reborn {
	typedef unsigned long ResourceTypeID;

	class AbstractResource {
	public:
		AbstractResource() = delete;
		AbstractResource(ResourceTypeID _type): type(_type) {
		}
		const ResourceTypeID& getType() const {
			return type;
		};
		bool isLoaded() const{
			return loaded;
		}
		bool notLoaded() const{
			return !isLoaded();
		}
		//загружает ресурс из ПОЛНОГО (абсолютный путь) имени файла 
		virtual bool tryLoad(const std::string& filename) = 0;
		virtual bool unload() = 0;
	protected:
		ResourceTypeID type;
		bool loaded = false;
	};
}