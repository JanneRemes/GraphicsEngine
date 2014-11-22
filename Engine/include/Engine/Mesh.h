
#ifndef MESH_H
#define MESH_H

#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>

class Mesh
{
public:
	Mesh() = delete;
	Mesh(const Mesh& other) = delete;
	Mesh(const VertexFormat& format);
	Mesh(const VertexFormat& format, const std::vector<GLfloat>& vertices);
	Mesh(const VertexFormat& format, const std::string& filepath);
	
	bool fromFile(const std::string& filepath);

	const VertexBuffer& getVertices() const;
	const IndexBuffer& getIndices() const;
private:
	VertexBuffer m_Vertices;
	IndexBuffer m_Indices;
};

#endif // Include guard
