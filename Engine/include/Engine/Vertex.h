
#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec3 Normal;
	glm::vec3 UV;
};

#endif // Include guard
