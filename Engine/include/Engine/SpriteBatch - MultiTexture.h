
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>
#include <Engine/Texture.h>
#include <Engine/Math.h>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <map>

struct Sprite
{
	typedef Texture* TexturePtr;

	glm::vec3 Position;
	glm::vec2 Size;
	float Rotation;

	glm::vec4 Color;
	glm::vec2 TexCoords[2];
	TexturePtr Texture;
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

	void Begin()
	{
		if (!m_IsDrawing)
		{
			std::
			m_IsDrawing = true;
		}
	}

	void End()
	{
		if (m_IsDrawing)
		{
			
			m_VertexBuffer.bind();
			m_IndexBuffer.bind();
			
			for (const auto& pair : m_Data)
			{
				const Texture& texture = *pair.first;
				const SpriteData& data = pair.second;

				m_VertexBuffer.setData(data.Vertices);
				m_

				gl::DrawElements(gl::TRIANGLES, m_Count * 6, gl::UNSIGNED_INT, data.Indices.data());
			}

			m_VertexBuffer.unbind();
			m_IndexBuffer.unbind();
			m_IsDrawing = false;
		}
	}

	void Draw(const Sprite& sprite)
	{
		size_t& count = m_Data[sprite.Texture].Count;

		if (count == m_Size)
		{
			End();
			Begin();
		}

		const glm::vec2 position[2]
		{
			Math::Rotate(glm::vec2(sprite.Position), sprite.Rotation),
			Math::Rotate(glm::vec2(sprite.Position) + sprite.Size, sprite.Rotation),
		};

		std::vector<Vertex>& vertices = m_Data[sprite.Texture].Vertices;

		vertices[count + 0].Position = { position[0].x, position[0].y, sprite.Position.z };
		vertices[count + 0].Color    = { sprite.Color };
		vertices[count + 0].UV       = { sprite.TexCoords[0].x, sprite.TexCoords[0].y };
		
		vertices[count + 1].Position = { position[0].x, position[1].y, sprite.Position.z };
		vertices[count + 1].Color    = { sprite.Color };
		vertices[count + 1].UV       = { sprite.TexCoords[0].x, sprite.TexCoords[1].y };
		
		vertices[count + 2].Position = { position[1].x, position[1].y, sprite.Position.z };
		vertices[count + 2].Color    = { sprite.Color };
		vertices[count + 2].UV       = { sprite.TexCoords[1].x, sprite.TexCoords[1].y };
		
		vertices[count + 3].Position = { position[1].x, position[0].y, sprite.Position.z };
		vertices[count + 3].Color    = { sprite.Color };
		vertices[count + 3].UV       = { sprite.TexCoords[1].x, sprite.TexCoords[0].y };

		count++;
	}
private:
	struct SpriteData
	{
		std::vector<Vertex> Vertices;
		std::vector<GLuint> Indices;
		size_t Count;
	};

	bool m_IsDrawing = false;
	size_t m_Size = 0;
	std::map<Texture*, SpriteData> m_Data;
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
};

#endif // Include guard
