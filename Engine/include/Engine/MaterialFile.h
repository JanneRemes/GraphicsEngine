
#ifndef MATERIAL_FILE_H
#define MATERIAL_FILE_H

#include <vector>

class Material;

class MaterialFile
{
	friend class Model;
public:
	~MaterialFile();
	bool loadFromFile(const std::string& filepath);
private:
	Material* findMaterial(const std::string& name) const;
	void clear();

	std::vector<Material*> m_Materials;
};

#endif
