
#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <Engine/VertexInfo.h>
#include <vector>

class VertexFormat
{
	static GLuint GetSize(const std::vector<VertexInfo>& vertices);
public:
	static const VertexFormat Position3f_Normal3f_UV2f;
	static const VertexFormat Position3f_Color4f_UV2f;
	static const VertexFormat Position3f_Color4f;
	static const VertexFormat Position3f;

	VertexFormat() = delete;
	VertexFormat(const VertexFormat& other) = default;
	VertexFormat(const std::vector<VertexInfo>& vertices);

	const std::vector<VertexInfo> Vertices;
	const GLuint Size;
};

#endif // Include guard
