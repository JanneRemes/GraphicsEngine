
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <wgl_core_2_1/wgl.h>
#include <unordered_map>
#include <Engine/Asset.h>
#include <Engine/Util.h>

typedef Asset* (*AssetLoadFunc)(const std::string&);

class AssetManager
{
public:
	typedef size_t AssetType;
	typedef size_t HashValue;

	/*
		[ Construct using defaults ]
	*/
	AssetManager() = default;

	/*
		[ Construct and set an initial root folder ]
		rootFolder: The initial root folder path
	*/
	AssetManager(const std::string& rootFolder);

	~AssetManager();

	template<class T>
	/*
		[ Register a function to handle the loading of new assets ]
		loadFunc: Pointer to the loader function
	*/
	void registerLoadFunc(const AssetLoadFunc loadFunc)
	{
		static_assert(std::is_base_of<Asset, T>::value, "Type must be derived from Asset");
		const AssetType type = Util::GetTypeId<T>();
		m_LoadFuncs[type] = loadFunc;
	}

	template<class T>
	/*
		[ Load an asset from a file ]
		filepath: Path to the asset file
		relative: Whether the path is relative to the root folder path
		  return: Pointer to the asset
	*/
	T* load(const std::string& filepath, bool relative = true)
	{
		static_assert(std::is_base_of<Asset, T>::value, "Type must be derived from Asset");
		const std::string fullpath = relative ? m_RootFolder + filepath : filepath;
		const HashValue hash = m_Hash(filepath);
		const AssetType type = Util::GetTypeId<T>();

		if (containsAsset(hash))
		{
			Asset* asset = m_Assets.at(hash);
			
			if (asset->m_Type == type)
			{
				asset->m_UseCount++;
				return static_cast<T*>(asset);
			}
			else
			{
				// Error: Asset type mismatch
				return nullptr;
			}
		}
		else
		{
			const AssetLoadFunc loadFunc = getLoadFunc(type);

			if (loadFunc)
			{
				Asset* newAsset = loadFunc(fullpath);

				if (newAsset)
				{
					newAsset->m_UseCount = 1;
					newAsset->m_Type = type;
					m_Assets[hash] = newAsset;
					return static_cast<T*>(newAsset);
				}
				else
				{
					// Error: Loading failed
					return nullptr;
				}
			}
			else
			{
				// Error: No loader registered
				return nullptr;
			}
		}
	}

	template<class T>
	/*
		[ Get the number of assets of a specific type ]
		return: The number of assets
	*/
	size_t getCount() const
	{
		const AssetType type = Util::GetTypeId<T>();
		size_t count = 0;

		for (const auto& pair : m_Assets)
		{
			if (pair.second->m_Type == type)
			{
				count++;
			}
		}

		return count;
	}

	/*
		[ Get the total number of assets ]
		return: The total number of assets
	*/
	size_t getCount() const;

	/*
		[ Unload an asset ]
		filepath: Path to the file, relative to the root folder
		   force: Forcefully unload the asset, even if it's still in use
		  return: 1 = The file was unloaded, 0 = The file's is still in use, -1 = The file does not exist
	*/
	int unload(const std::string& filepath, bool force = false);

	/*
		[ Unloads all assets ]
		filepath: Path to the file, relative to the root folder
		   force: Forcefully unload the assets, even if they're still in use
		  return: Number of unloaded assets
	*/
	size_t unloadAll(bool force = false);

	/*
		[ Set a new root folder ]
		newRoot: The new root folder path
	*/
	void setRootFolder(const std::string& newRoot);

	/*
		[ Get the current root folder ]
		return: The current root folder path
	*/
	const std::string getRootFolder() const;
private:
	const AssetLoadFunc getLoadFunc(AssetType type) const;
	bool containsLoadFunc(AssetType hash) const;
	bool containsAsset(HashValue hash) const;

	std::string m_RootFolder = "";
	std::hash<std::string> m_Hash;
	std::unordered_map<AssetType, AssetLoadFunc> m_LoadFuncs;
	std::unordered_map<HashValue, Asset*> m_Assets;
};

#endif // Include guard
