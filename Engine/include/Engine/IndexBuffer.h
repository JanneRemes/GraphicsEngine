
#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <Engine/Buffer.h>

class IndexBuffer : public Buffer<GLuint>
{
public:
	IndexBuffer()
		: Buffer(gl::ELEMENT_ARRAY_BUFFER, gl::DYNAMIC_DRAW)
	{
	}

	IndexBuffer(const std::vector<GLuint>& data)
		: Buffer(gl::ELEMENT_ARRAY_BUFFER, data, gl::DYNAMIC_DRAW)
	{
	}
};

#endif // Include guard
