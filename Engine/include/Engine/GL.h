
#ifndef EXTRA_GL_H
#define EXTRA_GL_H

#include <wgl_core_2_1/wgl.h>
#include <glm/glm.hpp>

struct VertexAttribute
{
	int Location;
	unsigned int Size;
	unsigned int ByteSize;
	char* Name;
};

namespace gl
{
	const VertexAttribute Position = { 0, 3, sizeof(glm::vec3), "Position" };
	const VertexAttribute Color    = { 1, 4, sizeof(glm::vec4), "Color" };
	const VertexAttribute Normal   = { 2, 3, sizeof(glm::vec3), "Normal" };
	const VertexAttribute UV       = { 3, 3, sizeof(glm::vec3), "UV" };

	void GetAllErrors();
}						  

#endif // Include guard
