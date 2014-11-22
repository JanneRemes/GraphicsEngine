
#include <Engine/Mesh.h>
#include <fstream>
#include <sstream>
#include <string>

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
	std::ifstream in(filepath);
	
	if (!in.is_open())
		return false;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;

	std::stringstream ss;
	std::string line;
	std::string prefix;

	while (!in.eof())
	{
		std::getline(in, line);

		if (in.fail())
			return false;

		ss.str("");
		ss.clear();
		ss << line;
		ss >> prefix >> std::ws;
		
		if (prefix == "v") // Vertex
		{
			GLfloat x, y, z;
			ss >> x >> y >> z >> std::ws;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			continue;
		}

		if (prefix == "vt") // TexCoord
		{
			GLfloat u, v;
			ss >> u >> v >> std::ws;
			texCoords.push_back(u);
			texCoords.push_back(v);
			continue;
		}

		if (prefix == "vn") // Normal
		{
			GLfloat x, y, z;
			ss >> x >> y >> z >> std::ws;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
			continue;
		}

		if (prefix == "f") // Index
		{
			for (size_t i = 0; i < 3; i++)
			{
				char ignore;
				GLfloat v, t, n;
				ss >> v >> ignore >> t >> ignore >> n >> std::ws;
				indices.push_back(v);
				indices.push_back(t);
				indices.push_back(n);
				continue;
			}
		}
	}

	m_Vertices.clear();
	m_Vertices.reserve((3 + 2 + 3) * (indices.size() / 3));

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		const GLuint iv = indices[i];		// Index - Vertex
		const GLuint it = indices[i + 1];	// Index - TexCoord
		const GLuint in = indices[i + 2];	// Index - Normal

		m_Vertices.append(
		{
			vertices[iv + 0],	// x
			vertices[iv + 1],	// y
			vertices[iv + 2],	// z

			texCoords[it + 0],	// u
			texCoords[it + 1],	// v

			normals[in + 0],	// x
			normals[in + 1],	// y
			normals[in + 2],	// z
		});

		m_Indices.append({ iv });
	}

	return true;
}

const VertexBuffer& Mesh::getVertices() const
{
	return m_Vertices;
} 

const IndexBuffer& Mesh::getIndices() const
{
	return m_Indices;
}
