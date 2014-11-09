
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <unordered_map>
#include <vector>
#include <memory>

/*
	[ Simple and fast utility, that loads files into memory in raw binary format ]
*/
class FileManager
{
	typedef std::vector<char> File;
	typedef std::shared_ptr<std::vector<char>> SharedFile;
private:
	const std::string m_RootFolder;
	std::unordered_map<size_t, SharedFile> m_Files;

	/*
		[ Attempt to read a file's data into memory ]
		fullpath: The entire path, including the root folder
		  return: Whether the file was loaded
	*/
	SharedFile read(const std::string& fullpath) const;
public:
	/*
		[ The object that's internally used to hash all filepaths ]
	*/
	static const std::hash<std::string> Hash;

	/*
		[ Construct a new FileManager using the specified root folder ]
		rootFolder: The root folder
	*/
	FileManager(const std::string& rootFolder = "");

	/*
		[ Attempt to load a single file ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file was loaded
	*/
	bool load(const std::string& filepath);

	/*
		[ Attempt to load a list of files ]
		filepaths: A list of paths, all relative to the root folder
		   return: The number of loaded files
	*/
	size_t loadAll(const std::vector<std::string>& filepaths);

	/*
		[ Attempt to unload a single file ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file was unloaded
	*/
	bool unload(const std::string& filepath);

	/*
		[ Attempt to unload a single file ]
		  hash: Hash of the root folder and a filepath
		return: Whether the file was unloaded
	*/
	bool unload(size_t hash);

	/*
		[ Attempt to unload all files ]
		return:	The number of unloaded files
	*/
	size_t unloadAll();

	/*
		[ Get the total number of loaded files ]
		return:	The number of files
	*/
	size_t getCount() const;

	/*
		[ Get whether or not a file is loaded ]
		filepath: Path to the file, relative to the root folder
		  return: Whether the file is loaded
	*/
	bool isLoaded(const std::string& filepath) const;

	/*
		[ Get whether or not a file is loaded ]
		    hash: Hash of the root folder and a filepath
		  return: Whether the file is loaded
	*/
	bool isLoaded(size_t hash) const;

	/*
		[ Get the root folder ]
		return: The root folder
	*/
	const std::string& getRootFolder() const;

	/*
		[ Get a pointer to a file's data ]
		filepath: Path to the file, relative to the root folder
		  return: A shared_ptr to the file data, or nullptr if it doesn't exist
	*/
	SharedFile get(const std::string& filepath) const;

	/*
		[ Get a pointer to a file's data ]
		  hash: Hash of the root folder and a filepath
		return: A shared_ptr to the file data, or nullptr if it doesn't exist
	*/
	SharedFile get(size_t hash) const;
};

#endif // Include guard
