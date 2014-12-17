
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
	glm::vec3 tf;
	uint32_t illum;
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ke;
	std::string map_kd;
};

#endif
