
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <Engine/Graphics.h>
#include <glew/glew.h>
#include <vector>

class SpriteBatch
{
public:
	SpriteBatch()
	{
		vao = GL::GenVertexArray();
		GL::BindVertexArray(vao);

		ebo = GL::GenBuffer();
		GL::BindBuffer(GL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER, ebo);
		GL::BufferData(GL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER, 0, nullptr, GL::BufferUsage::DYNAMIC_DRAW);

		vbo = GL::GenBuffer();
		GL::BindBuffer(GL::BufferBindingTarget::ARRAY_BUFFER, vbo);
		GL::BufferData(GL::BufferBindingTarget::ARRAY_BUFFER, 0, nullptr, GL::BufferUsage::DYNAMIC_DRAW);

		GL::EnableVertexAttribArray(Graphics::Position.Location);
		GL::EnableVertexAttribArray(Graphics::Color.Location);
		GL::EnableVertexAttribArray(Graphics::UV.Location);

		unsigned int stride =
			Graphics::Position.Size +
			Graphics::Color.Size +
			Graphics::UV.Size;

		GL::VertexAttribPointer(
			Graphics::Position.Location, Graphics::Position.Size,
			GL::Type::FLOAT, false, stride, vertices.data());

		GL::VertexAttribPointer(
			Graphics::Color.Location, Graphics::Color.Size,
			GL::Type::FLOAT, false, stride,
			vertices.data() + Graphics::Position.Size);

		GL::VertexAttribPointer(
			Graphics::UV.Location, Graphics::UV.Size,
			GL::Type::FLOAT, false, stride,
			vertices.data() + Graphics::Position.Size + Graphics::Color.Size);

		GL::BindVertexArray(0);
	}

	~SpriteBatch()
	{
		GL::DeleteVertexArray(vao);
		GL::DeleteBuffer(vbo);
		GL::DeleteBuffer(ebo);
	}

	void Start()
	{
		vertices.clear();
		indices.clear();
	}

	void Draw(const std::vector<float>& newVertices)
	{
		const unsigned int index = indices.size();
		const auto newIndices =
		{
			index + 0, index + 1, index + 2,
			index + 2, index + 3, index + 0,
		};

		vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
		indices.insert(indices.end(), newIndices.begin(), newIndices.end());
	}

	void End()
	{
		GL::BindVertexArray(vao);
		GL::BufferSubData(GL::BufferBindingTarget::ARRAY_BUFFER, 0, vertices.size(), vertices.data());
		GL::BufferSubData(GL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER, 0, indices.size(), indices.data());
		GL::DrawElements(GL::Mode::TRIANGLES, indices.size() / 3, GL::Type::UNSIGNED_INT, indices.data());
		GL::BindVertexArray(0);
	}

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};

#endif // Include guard
