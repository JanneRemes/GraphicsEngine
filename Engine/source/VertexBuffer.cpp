
#include <Engine/VertexBuffer.h>

VertexBuffer::VertexBuffer(const VertexFormat& format)
	: Buffer(format.Size, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
	, m_Format(format)
{
}

VertexBuffer::VertexBuffer(const VertexFormat& format, const std::vector<GLfloat>& vertices)
	: VertexBuffer(format)
{
	m_Buffer.assign(vertices.begin(), vertices.end());
}

const VertexFormat& VertexBuffer::getFormat() const
{
	return m_Format;
}
