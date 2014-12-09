
#ifndef MESH_H
#define MESH_H

#include <Engine/Material.h>
#include <Engine/Vertex.h>

struct Mesh final
{
	std::string Name;
	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;
	Material* m_Material;
};

#endif // Include guard
