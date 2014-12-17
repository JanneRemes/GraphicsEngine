
#include <Engine/MaterialFile.h>
#include <Engine/Material.h>
#include <fstream>
#include <sstream>
#include <cstdint>

MaterialFile::~MaterialFile()
{
	clear();
}

bool MaterialFile::loadFromFile(const std::string& filepath)
{
	std::ifstream in(filepath);

	if (!in)
		return false;

	clear();

	std::stringstream ss;
	std::string line, prefix;
	Material* currentMaterial = nullptr;

	while (!in.eof())
	{
		std::getline(in, line);

		if (in.bad())
			return false;

		ss.clear();
		ss.str(line);
		ss >> prefix >> std::ws;

		if (prefix == "newmtl")
		{
			currentMaterial = new Material;
			memset(currentMaterial, 0, sizeof(Material));
			ss >> currentMaterial->name >> std::ws;
			m_Materials.push_back(currentMaterial);
			continue;
		}

		if (!currentMaterial)
			continue;

		if (prefix == "Ns")
		{
			ss >> currentMaterial->ns >> std::ws;
			continue;
		}

		if (prefix == "Ni")
		{
			ss >> currentMaterial->ni >> std::ws;
			continue;
		}

		if (prefix == "d")
		{
			ss >> currentMaterial->d >> std::ws;
			continue;
		}

		if (prefix == "Tr")
		{
			ss >> currentMaterial->tr >> std::ws;
			continue;
		}

		if (prefix == "Tf")
		{
			ss >> currentMaterial->tf.r >> std::ws;
			ss >> currentMaterial->tf.g >> std::ws;
			ss >> currentMaterial->tf.b >> std::ws;
			continue;
		}

		if (prefix == "illum")
		{
			ss >> currentMaterial->illum >> std::ws;
			continue;
		}

		if (prefix == "Ka")
		{
			ss >> currentMaterial->ka.r >> std::ws;
			ss >> currentMaterial->ka.g >> std::ws;
			ss >> currentMaterial->ka.b >> std::ws;
			continue;
		}

		if (prefix == "Kd")
		{
			ss >> currentMaterial->kd.r >> std::ws;
			ss >> currentMaterial->kd.g >> std::ws;
			ss >> currentMaterial->kd.b >> std::ws;
			continue;
		}

		if (prefix == "Ks")
		{
			ss >> currentMaterial->ks.r >> std::ws;
			ss >> currentMaterial->ks.g >> std::ws;
			ss >> currentMaterial->ks.b >> std::ws;
			continue;
		}

		if (prefix == "Ke")
		{
			ss >> currentMaterial->ke.r >> std::ws;
			ss >> currentMaterial->ke.g >> std::ws;
			ss >> currentMaterial->ke.b >> std::ws;
			continue;
		}

		if (prefix == "map_Kd")
		{
			ss >> currentMaterial->map_kd >> std::ws;
			continue;
		}
	}

	return true;
}

Material* MaterialFile::findMaterial(const std::string& name) const
{
	for (auto& material : m_Materials)
	{
		if (material->name == name)
			return material;
	}

	return nullptr;
}

void MaterialFile::clear()
{
	for (auto& e : m_Materials)
		delete e;
	m_Materials.clear();
}
