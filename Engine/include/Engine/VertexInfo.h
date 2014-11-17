
#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include <glew/glew.h>
#include <string>

struct VertexInfo
{
	VertexInfo() = delete;
	VertexInfo(const VertexInfo& other) = default;
	VertexInfo(GLuint size);
	VertexInfo(GLuint size, GLuint location, const std::string& name);

	GLuint size;
	GLuint location;
	std::string name;
};

#endif // Include guard
