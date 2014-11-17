
#include <Engine/IndexBuffer.h>

IndexBuffer::IndexBuffer()
	: Buffer(1, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
{
}

IndexBuffer::IndexBuffer(const std::vector<GLuint>& indices)
	: IndexBuffer()
{
	m_Buffer.assign(indices.begin(), indices.end());
}
