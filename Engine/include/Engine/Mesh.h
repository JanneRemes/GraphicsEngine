
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
	std::vector<Vertex> vertexData;
	std::vector<uint32_t> indices;
};

#endif
