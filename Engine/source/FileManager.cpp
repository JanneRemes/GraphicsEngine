
#include <Engine/FileManager.h>
#include <Engine/Util.h>
#include <future>

const std::hash<std::string> FileManager::Hash;

FileManager::SharedFile FileManager::read(const std::string& fullpath) const
{
	std::fstream in(fullpath, std::ios_base::in | std::ios_base::binary);

	if (in.is_open())
	{
		SharedFile file = std::make_shared<File>();
		file->reserve(static_cast<size_t>(Util::GetFileSize(in)));
		char c;

		while (true)
		{
			c = in.get();

			if (in.eof())
				break;

			if (in.fail())
				return nullptr; // Error: Unable to read file

			file->push_back(c);
		}

		file->shrink_to_fit();
		return file;
	}

	return nullptr; // Error: Unable to open file
}
	
FileManager::FileManager(const std::string& rootFolder)
	: m_RootFolder(rootFolder)
{
}

bool FileManager::load(const std::string& filepath)
{
	const std::string fullpath = m_RootFolder + filepath;
	const size_t hash = Hash(fullpath);

	if (!isLoaded(hash))
	{
		SharedFile file(read(fullpath));

		if (file)
		{
			m_Files.insert(std::make_pair(hash, file));
			return true;
		}
	}

	return false;
}

size_t FileManager::loadAll(const std::vector<std::string>& filepaths)
{
	std::vector<size_t> hashes;
	std::vector<std::future<SharedFile>> files;
		
	for (const auto& filepath : Util::GetUnique(filepaths))
	{
		const std::string fullpath = m_RootFolder + filepath;
		const size_t hash = Hash(fullpath);

		if (!isLoaded(hash))
		{
			hashes.push_back(hash);
			files.push_back(std::async([=]() { return read(fullpath); }));
		}
	}

	size_t count = 0;

	for (size_t i = 0; i < files.size(); i++)
	{
		SharedFile file(files[i].get());

		if (file)
		{
			m_Files.insert(std::make_pair(hashes[i], file));
			count++;
		}
	}

	return count;
}

bool FileManager::unload(const std::string& filepath)
{
	return unload(Hash(m_RootFolder + filepath));
}

bool FileManager::unload(size_t hash)
{
	const auto it = m_Files.find(hash);

	if ((it != m_Files.end()) &&
		(it->second.use_count() == 1))
	{
		m_Files.erase(it);
		return true;
	}
		
	return false; // Error: File doesn't exist
}

size_t FileManager::unloadAll()
{
	std::vector<decltype(m_Files.begin())> removed;

	for (auto it = m_Files.begin(); it != m_Files.end(); it++)
	{
		if (it->second.use_count() == 1)
		{
			removed.emplace_back(it);
		}
	}

	for (const auto& it : removed)
	{
		m_Files.erase(it);
	}

	return removed.size();
}

size_t FileManager::getCount() const
{
	return m_Files.size();
}

bool FileManager::isLoaded(const std::string& filepath) const
{
	return isLoaded(Hash(m_RootFolder + filepath));
}

bool FileManager::isLoaded(size_t hash) const
{
	return m_Files.find(hash) != m_Files.end();
}

const std::string& FileManager::getRootFolder() const
{
	return m_RootFolder;
}

FileManager::SharedFile FileManager::get(const std::string& filepath) const
{
	return get(Hash(m_RootFolder + filepath));
}

FileManager::SharedFile FileManager::get(size_t hash) const
{
	const auto it = m_Files.find(hash);

	if (it != m_Files.end())
	{
		return it->second;
	}

	return nullptr;
}
