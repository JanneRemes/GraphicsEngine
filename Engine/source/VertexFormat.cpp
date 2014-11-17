
#include <Engine/VertexFormat.h>

GLuint VertexFormat::GetSize(const std::vector<VertexInfo>& vertices)
{
	GLuint size = 0;
	for (const auto& e : vertices) { size += e.size; }
	return size;
}

VertexFormat::VertexFormat(const std::vector<VertexInfo>& vertices)
	: Vertices(vertices)
	, Size(GetSize(vertices))
{
}

/*
	Vertex Format samples
*/
const VertexFormat VertexFormat::Position3f_Normal3f_UV2f(
{
	{ 3, 0, "Position" },
	{ 3, 1, "Normal" },
	{ 2, 2, "UV" },
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
