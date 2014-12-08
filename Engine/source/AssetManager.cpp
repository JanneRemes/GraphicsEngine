
#include <Engine/AssetManager.h>

AssetManager::AssetManager(const std::string& rootFolder)
{
	setRootFolder(rootFolder);
}

AssetManager::~AssetManager()
{
	unloadAll(true);
}

size_t AssetManager::getCount() const
{
	return m_Assets.size();
}

int AssetManager::unload(const std::string& filepath, bool force)
{
	const HashValue hash = m_Hash(filepath);

	if (containsAsset(hash))
	{
		if (force)
		{
			delete m_Assets.at(hash);
			m_Assets.erase(hash);
			return 1;
		}
		else
		{
			Asset* asset = m_Assets.at(hash);

			if (asset->m_UseCount-- == 1)
			{
				delete asset;
				m_Assets.erase(hash);
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return -1;
	}
}

size_t AssetManager::unloadAll(bool force)
{
	size_t unloadCount = 0;

	if (force)
	{
		for (auto& pair : m_Assets)
			delete pair.second;
		m_Assets.clear();
	}
	else
	{
		auto it = m_Assets.begin();

		while (it != m_Assets.end())
		{
			auto asset = it->second;

			if (asset->m_UseCount-- == 1)
			{
				m_Assets.erase(it++);
				unloadCount++;
			}
			else
			{
				it++;
			}
		}
	}

	return unloadCount;
}

void AssetManager::setRootFolder(const std::string& newRoot)
{
	if (!newRoot.empty() && newRoot.back() != '\\')
		m_RootFolder = newRoot + "\\";
	else
		m_RootFolder = newRoot;
}

const std::string AssetManager::getRootFolder() const
{
	return m_RootFolder;
}

const AssetLoadFunc AssetManager::getLoadFunc(AssetType type) const
{
	if (containsLoadFunc(type))
		return m_LoadFuncs.at(type);
	return nullptr;
}

bool AssetManager::containsLoadFunc(AssetType hash) const
{
	return m_LoadFuncs.find(hash) != m_LoadFuncs.end();
}

bool AssetManager::containsAsset(HashValue hash) const
{
	return m_Assets.find(hash) != m_Assets.end();
}
