
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <Engine/Buffer.h>

class IndexBuffer : public Buffer<GLuint>
{
public:
	IndexBuffer();
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer(const std::vector<GLuint>& indices);
};

#endif // Include guard
