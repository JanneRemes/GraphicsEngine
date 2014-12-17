
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <cstdint>
#include <vector>

class Material;

class Mesh
{
public:
	std::string name;
	Material* material;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> texCoords;
	std::vector<uint32_t> indices;
};

#endif
