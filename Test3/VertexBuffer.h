
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Buffer.h"

/*
	VertexInfo
*/
struct VertexInfo
{
	VertexInfo() = delete;
	VertexInfo(const VertexInfo& other) = default;

	VertexInfo(GLuint size, GLuint location, const std::string& name)
		: size(size)
		, location(location)
		, name(name)
	{
	}

	VertexInfo(GLuint size)
		: VertexInfo(size, -1, "")
	{
	}

	GLuint size;
	GLuint location;
	std::string name;
};

/*
	VertexFormat
*/
class VertexFormat
{
	static GLuint GetSize(const std::vector<VertexInfo>& vertices)
	{
		GLuint size = 0;
		for (const auto& e : vertices) { size += e.size; }
		return size;
	}
public:
	static const VertexFormat Position3f_Color4f_UV2f;
	static const VertexFormat Position3f_Color4f;
	static const VertexFormat Position3f;

	VertexFormat() = delete;
	VertexFormat(const VertexFormat& other) = default;

	VertexFormat(const std::vector<VertexInfo>& vertices)
		: Vertices(vertices)
		, Size(GetSize(vertices))
	{
	}

	const std::vector<VertexInfo> Vertices;
	const GLuint Size;
};

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

/*
	VertexBuffer
*/
class VertexBuffer : public Buffer<GLfloat>
{
	static bool ValidateFormat(const std::vector<GLfloat>& data);
public:
	VertexBuffer() = delete;
	VertexBuffer(const VertexBuffer& other) = delete;

	VertexBuffer(const VertexFormat& format)
		: Buffer(format.Size, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
		, m_Format(format)
	{
	}

	VertexBuffer(const VertexFormat& format, const std::vector<GLfloat>& vertices)
		: VertexBuffer(format)
	{
		m_Buffer.assign(vertices.begin(), vertices.end());
	}

	const VertexFormat& getFormat() const
	{
		return m_Format;
	}
private:
	const VertexFormat m_Format;
};

#endif // Include guard
