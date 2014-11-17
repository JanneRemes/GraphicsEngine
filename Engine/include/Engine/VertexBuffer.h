
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <Engine/Buffer.h>
#include <Engine/VertexFormat.h>

class VertexBuffer : public Buffer<GLfloat>
{
public:
	VertexBuffer() = delete;
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer(const VertexFormat& format);
	VertexBuffer(const VertexFormat& format, const std::vector<GLfloat>& vertices);

	const VertexFormat& getFormat() const;
private:
	const VertexFormat m_Format;
};

#endif // Include guard
