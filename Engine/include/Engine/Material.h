
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>
#include <cstdint>

class Material
{
public:
	std::string name;
	float ns;
	float ni;
	float d;
	float tr;
	glm::vec4 tf;
	uint32_t illum;
	glm::vec4 ka;
	glm::vec4 kd;
	glm::vec4 ks;
	glm::vec4 ke;
	std::string map_kd;
};

#endif
