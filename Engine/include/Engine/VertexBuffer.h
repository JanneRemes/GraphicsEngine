
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <Engine/Buffer.h>
#include <Engine/GL.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 UV;
};

class VertexBuffer : public Buffer<Vertex>
{
public:
	VertexBuffer()
		: Buffer(gl::ARRAY_BUFFER, gl::DYNAMIC_DRAW)
	{
	}

	VertexBuffer(const std::vector<Vertex>& data)
		: Buffer(gl::ARRAY_BUFFER, data, gl::DYNAMIC_DRAW)
	{
	}

	void bind() override
	{
		Buffer::bind();

		gl::EnableVertexAttribArray(gl::Position.Location);
		gl::EnableVertexAttribArray(gl::Color.Location);
		gl::EnableVertexAttribArray(gl::UV.Location);

		gl::VertexAttribPointer(gl::Position.Location, gl::Position.Size, gl::FLOAT, false, sizeof(Vertex), (void*)(0));
		gl::VertexAttribPointer(gl::Normal.Location,   gl::Normal.Size,   gl::FLOAT, false, sizeof(Vertex), (void*)(0 + gl::Position.ByteSize));
		gl::VertexAttribPointer(gl::Color.Location,    gl::Color.Size,    gl::FLOAT, false, sizeof(Vertex), (void*)(0 + gl::Position.ByteSize + gl::Normal.ByteSize));
		gl::VertexAttribPointer(gl::UV.Location,       gl::UV.Size,       gl::FLOAT, false, sizeof(Vertex), (void*)(0 + gl::Position.ByteSize + gl::Normal.ByteSize + gl::Color.ByteSize));
	}
};

#endif // Include guard
