
#include <Engine/VertexFormat.h>

GLuint VertexFormat::GetSize(const std::vector<VertexInfo>& vertices)
{
	GLuint size = 0;
	for (const auto& e : vertices) { size += e.size; }
	return size;
}

VertexFormat::VertexFormat(const std::vector<VertexInfo>& vertices)
	: Vertices(vertices)
	, Size(GetSize(vertices) * sizeof(GLfloat))
{
}

/*
	Vertex Format examples
*/
const VertexFormat VertexFormat::Position3f_Normal3f_UV2f(
{
	{ 3, 0, "Position" },
	{ 2, 1, "UV" },
	{ 3, 2, "Normal" },
});

const VertexFormat VertexFormat::Position3f_Color4f_UV2f(
{
	{ 3, 0, "Position" },
	{ 4, 1, "Color" },
	{ 2, 2, "UV" },
});

const VertexFormat VertexFormat::Position3f_Color4f(
{
	{ 3, 0, "Position" },
	{ 4, 1, "Color" },
});

const VertexFormat VertexFormat::Position3f(
{
	{ 3, 0, "Position" },
});
