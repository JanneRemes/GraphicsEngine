
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <Engine/Buffer.h>

class IndexBuffer : public Buffer<GLuint>
{
public:
	IndexBuffer()
		: Buffer(gl::ARRAY_BUFFER, gl::DYNAMIC_DRAW)
	{
	}

	IndexBuffer(const std::vector<GLuint>& data)
		: Buffer(gl::ARRAY_BUFFER, data, gl::DYNAMIC_DRAW)
	{
	}
};

#endif // Include guard
