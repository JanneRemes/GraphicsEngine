
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>
#include <Engine/Math.h>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <map>

struct Sprite
{
	glm::vec3 Position;
	glm::vec2 Size;
	float Rotation;

	glm::vec4 Color;
	glm::vec2 TexCoords[2];
};

class SpriteBatch
{
public:
	SpriteBatch(size_t size)
		: m_Size(size)
		, m_Vertices(size * 4)
		, m_Indices(size * 6)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_Indices[i + 0] = i + 0;
			m_Indices[i + 1] = i + 1;
			m_Indices[i + 2] = i + 2;

			m_Indices[i + 3] = i + 2;
			m_Indices[i + 4] = i + 3;
			m_Indices[i + 5] = i + 0;
		}
	}

	void Begin(Texture* texture, Shader* shader)
	{
		if (!m_IsDrawing)
		{
			m_Texture = texture;
			m_Shader = shader;
			m_Count = 0;
			m_IsDrawing = true;
		}
	}

	void End()
	{
		if (m_IsDrawing)
		{
			m_VertexBuffer.setData(m_Vertices);
			m_VertexBuffer.bind();
			m_IndexBuffer.setData(m_Indices);
			m_IndexBuffer.bind();
			m_Shader->bind();
			m_Texture->bind();
			
			gl::DrawElements(gl::TRIANGLES, m_Count * 6, gl::UNSIGNED_INT, m_Indices.data());
			
			m_Texture->unbind();
			m_Shader->unbind();
			m_VertexBuffer.unbind();
			m_IndexBuffer.unbind();
			m_IsDrawing = false;
		}
	}

	void Draw(const Sprite& sprite)
	{
		if (m_Count >= m_Size)
		{
			End();
			Begin(m_Texture, m_Shader);
		}

		const glm::vec2 position[2]
		{
			Math::Rotate(glm::vec2(sprite.Position), sprite.Rotation),
			Math::Rotate(glm::vec2(sprite.Position) + sprite.Size, sprite.Rotation),
		};

		m_Vertices[m_Count + 0].Position = { position[0].x, position[0].y, sprite.Position.z };
		m_Vertices[m_Count + 0].Color    = { sprite.Color };
		m_Vertices[m_Count + 0].UV       = { sprite.TexCoords[0].x, sprite.TexCoords[0].y };

		m_Vertices[m_Count + 1].Position = { position[0].x, position[1].y, sprite.Position.z };
		m_Vertices[m_Count + 1].Color    = { sprite.Color };
		m_Vertices[m_Count + 1].UV       = { sprite.TexCoords[0].x, sprite.TexCoords[1].y };

		m_Vertices[m_Count + 2].Position = { position[1].x, position[1].y, sprite.Position.z };
		m_Vertices[m_Count + 2].Color    = { sprite.Color };
		m_Vertices[m_Count + 2].UV       = { sprite.TexCoords[1].x, sprite.TexCoords[1].y };

		m_Vertices[m_Count + 3].Position = { position[1].x, position[0].y, sprite.Position.z };
		m_Vertices[m_Count + 3].Color    = { sprite.Color };
		m_Vertices[m_Count + 3].UV       = { sprite.TexCoords[1].x, sprite.TexCoords[0].y };

		m_Count++;
	}
private:
	bool m_IsDrawing = false;
	size_t m_Count = 0;
	size_t m_Size = 0;
	Texture* m_Texture = nullptr;
	Shader* m_Shader = nullptr;
	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
};

#endif // Include guard
