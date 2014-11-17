
#include <Engine/VertexInfo.h>

VertexInfo::VertexInfo(GLuint size)
	: VertexInfo(size, -1, "")
{
}

VertexInfo::VertexInfo(GLuint size, GLuint location, const std::string& name)
	: size(size)
	, location(location)
	, name(name)
{
}
