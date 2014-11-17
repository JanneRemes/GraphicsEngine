
#include <Engine/Mesh.h>

Mesh::Mesh(const VertexFormat& format)
	: m_Vertices(format)
{
}

Mesh::Mesh(const VertexFormat& format, const std::vector<GLfloat>& vertices)
	: m_Vertices(format, vertices)
{
}

Mesh::Mesh(const VertexFormat& format, const std::string& filepath)
	: m_Vertices(format)
{
	if (!fromFile(filepath))
	{
		throw std::runtime_error("Error: Unable to load Mesh");
	}
}

bool Mesh::fromFile(const std::string& filepath)
{
	return false; // TODO: use MeshLoader here
}
