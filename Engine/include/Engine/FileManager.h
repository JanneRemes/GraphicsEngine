
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <memory>
#include <vector>
#include <future>
#include <unordered_map>

#include <Engine/Util.h>

class FileManager
{
	typedef std::vector<char> File;
	typedef std::shared_ptr<std::vector<char>> SharedFile;

	const std::string m_RootFolder;
	std::unordered_map<size_t, SharedFile> m_Files;

	/*
		[ Attempt to read a file's data into memory ]
		fullpath: The entire path, including the root folder
		  return: Whether the file was loaded
	*/
	SharedFile read(const std::string& fullpath)
	{
		std::fstream in(fullpath, std::ios_base::in | std::ios_base::binary);

		if (in.is_open()) // Error: Unable to open file
		{
			SharedFile file = std::make_shared<File>();
			file->reserve(static_cast<size_t>(Util::GetFileSize(in)));

			while (true)
			{
				file->push_back(in.get());

				if (in.eof())
				{
					file->push_back(0);
					break;
				}

				if (in.fail())
					return nullptr; // Error: Unable to read file
			}

			return file;
		}

		return nullptr;
	}
public:
	/*
		[ The object that's internally used to hash all paths ]
	*/
	static const std::hash<std::string> Hash;

	/*
		[ Construct a new FileManager using the specified root folder ]
		rootFolder: The root folder
	*/
	FileManager(const std::string& rootFolder = "")
		: m_RootFolder(rootFolder)
	{
	}

	/*
		[ Attempt to load a single file ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file was loaded
	*/
	bool load(const std::string& filepath)
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

	/*
		[ Attempt to load a list of files ]
		filepaths: A list of paths, all relative to the root folder
		   return: The number of loaded files
	*/
	size_t loadAll(const std::vector<std::string>& filepaths)
	{
		std::vector<size_t> hashes;
		std::vector<std::future<SharedFile>> files;
		
		for (const auto& filepath : filepaths)
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

	/*
		[ Attempt to unload a single file ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file was unloaded
	*/
	bool unload(const std::string& filepath)
	{
		const auto it = m_Files.find(Hash(m_RootFolder + filepath));

		if ((it != m_Files.end()) &&
			(it->second.use_count() == 1))
		{
			m_Files.erase(it);
			return true;
		}

		return false; // Error: File doesn't exist
	}

	/*
		[ Attempt to unload a single file ]
		  hash: Hash of the root folder and a filepath
		return: Whether the file was unloaded
	*/
	bool unload(size_t hash)
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

	/*
		[ Attempt to unload all files ]
		return:	The number of unloaded files
	*/
	size_t unloadAll()
	{
		std::vector<decltype(m_Files.begin())> removed;

		for (auto it = m_Files.begin(); it != m_Files.end(); it++)
		{
			if (it->second.use_count() == 1)
			{
				removed.emplace_back(it);
			}
		}

		for (const auto& e : removed)
		{
			m_Files.erase(e);
		}

		return removed.size();
	}

	/*
		[ Get the total number of loaded files ]
		return:	The number of files
	*/
	size_t getCount() const
	{
		return m_Files.size();
	}

	/*
		[ Get whether or not a file is loaded ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file is loaded
	*/
	bool isLoaded(const std::string& filepath) const
	{
		return m_Files.find(Hash(m_RootFolder + filepath)) != m_Files.end();
	}

	/*
		[ Get whether or not a file is loaded ]
		    hash: Hash of the root folder and a filepath
		  return: Whether the file is loaded
	*/
	bool isLoaded(size_t hash) const
	{
		return m_Files.find(hash) != m_Files.end();
	}

	/*
		[ Get the root folder ]
		return: The root folder
	*/
	const std::string& getRootFolder() const
	{
		return m_RootFolder;
	}

	/*
		[ Get a pointer to a file's data ]
		filepath: Path to the file, relative to the root folder
		  return: A shared_ptr to the file data, or nullptr if it doesn't exist
	*/
	SharedFile get(const std::string& filepath)
	{
		const auto it = m_Files.find(Hash(m_RootFolder + filepath));

		if (it != m_Files.end())
		{
			return it->second;
		}

		return nullptr;
	}

	/*
		[ Get a pointer to a file's data ]
		  hash: Hash of the root folder and a filepath
		return: A shared_ptr to the file data, or nullptr if it doesn't exist
	*/
	SharedFile get(size_t hash)
	{
		const auto it = m_Files.find(hash);

		if (it != m_Files.end())
		{
			return it->second;
		}

		return nullptr;
	}
};

const std::hash<std::string> FileManager::Hash;

#endif // Include guard
