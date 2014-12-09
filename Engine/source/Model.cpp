
#include <Engine/Model.h>
#include <fstream>
#include <sstream>

bool Model::fromFile(const std::string& filepath)
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

		if (prefix == "vn")
		{
			glm::vec3 vn;
			ss >> vn.x >> std::ws
			   >> vn.y >> std::ws
			   >> vn.z >> std::ws;
			continue;
		}

		if (prefix == "example")
		{
			GLfloat f;
			ss >> f >> std::ws;
			continue;
		}
	}

	return true;
}
