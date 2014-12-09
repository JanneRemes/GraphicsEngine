
#include <Engine/Material.h>
#include <fstream>
#include <sstream>

Material::Material()
{
	memset(this, 0, sizeof(Material));
}

bool Material::fromFile(const std::string& filepath)
{
	std::ifstream in(filepath);
		
	if (!in.is_open())
		return false;

	std::stringstream ss;
	std::string line;
	std::string prefix;

	while (std::getline(in, line))
	{
		if (in.fail())
		{
			return false;
		}

		ss.str("");
		ss.clear();
		ss << line;
		ss >> prefix >> std::ws;

		if (prefix.empty() || prefix == "#")
		{
			continue;
		}

		if (prefix == "newmtl")
		{
			ss >> newmtl >> std::ws;
			continue;
		}

		if (prefix == "Ns")
		{
			ss >> Ns >> std::ws;
			continue;
		}

		if (prefix == "Ni")
		{
			ss >> Ni >> std::ws;
			continue;
		}

		if (prefix == "d")
		{
			ss >> d >> std::ws;
			continue;
		}

		if (prefix == "Tr")
		{
			ss >> Tr >> std::ws;
			continue;
		}

		if (prefix == "Tf")
		{
			ss >> Tf.r >> std::ws
				>> Tf.g >> std::ws
				>> Tf.b >> std::ws;
			continue;
		}

		if (prefix == "illum")
		{
			ss >> illum >> std::ws;
			continue;
		}

		if (prefix == "Ka")
		{
			ss >> Ka.r >> std::ws
				>> Ka.g >> std::ws
				>> Ka.b >> std::ws;
			continue;
		}

		if (prefix == "Kd")
		{
			ss >> Kd.r >> std::ws
				>> Kd.g >> std::ws
				>> Kd.b >> std::ws;
			continue;
		}

		if (prefix == "Ks")
		{
			ss >> Ks.r >> std::ws
				>> Ks.g >> std::ws
				>> Ks.b >> std::ws;
			continue;
		}

		if (prefix == "Ke")
		{
			ss >> Ke.r >> std::ws
				>> Ke.g >> std::ws
				>> Ke.b >> std::ws;
			continue;
		}

		if (prefix == "map_Kd")
		{
			ss >> map_Kd >> std::ws;
			continue;
		}
	}

	return true;
}
