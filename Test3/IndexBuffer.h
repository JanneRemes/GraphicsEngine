
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Buffer.h"

class IndexBuffer : public Buffer<GLuint>
{
public:
	IndexBuffer(const IndexBuffer& other) = delete;

	IndexBuffer()
		: Buffer(1, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
	{
	}

	IndexBuffer(const std::vector<GLuint>& indices)
		: IndexBuffer()
	{
		m_Buffer.assign(indices.begin(), indices.end());
	}
};

#endif // Include guard
