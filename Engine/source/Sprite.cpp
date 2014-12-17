
#include <Engine/Sprite.h>
#include <Engine/Math.h>

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, Texture& texture)
	: m_Position(position)
	, m_Size(size)
	, m_Texture(&texture)
{
}

void Sprite::setPosition(const glm::vec3& position)
{
	m_Position = position;
	m_HasChanged = true;
}

void Sprite::setSize(const glm::vec2& size)
{
	m_Size = size;
	m_HasChanged = true;
}

void Sprite::setRotation(float rotation)
{
	m_Rotation = rotation;
	m_HasChanged = true;
}

void Sprite::setColor(const glm::vec4& color)
{
	m_Color = color;
	m_HasChanged = true;
}

void Sprite::setTexCoords(const glm::vec2& from, const glm::vec2& to)
{
	m_TexCoords = { from.x, from.y, to.x, to.y };
	m_HasChanged = true;
}

void Sprite::setTexture(Texture& texture)
{
	m_Texture = &texture;
}

const glm::vec3& Sprite::getPosition() const
{
	return m_Position;
}

const glm::vec2& Sprite::getSize() const
{
	return m_Size;
}

float Sprite::getRotation() const
{
	return m_Rotation;
}

const glm::vec4& Sprite::getColor() const
{
	return m_Color;
}

const glm::vec4& Sprite::getTexCoords() const
{
	return m_TexCoords;
}

Texture* Sprite::getTexture() const
{
	return m_Texture;
}

void Sprite::draw(Shader& shader)
{
	if (m_HasChanged)
		update();

	m_Vertices.bind();
	m_Indices.bind();
	shader.bind();

	if (m_Texture != nullptr)
	{
		m_Texture->bind();
		gl::DrawElements(gl::TRIANGLES, m_Indices.getSize(), gl::UNSIGNED_INT, 0);
		m_Texture->unbind();
	}
	else
	{
		gl::DrawElements(gl::TRIANGLES, m_Indices.getSize(), gl::UNSIGNED_INT, 0);
	}

	shader.unbind();
	m_Indices.unbind();
	m_Vertices.unbind();
}

std::vector<Vertex> Sprite::generateVertexData() const
{
	const glm::vec2 position[2]
	{
		math::Rotate(glm::vec2(m_Position) - m_Size * 0.5f, m_Rotation),
		math::Rotate(glm::vec2(m_Position) + m_Size * 0.5f, m_Rotation),
	};

	return std::vector<Vertex>
	{
		// Position, Normal, Color, TexCoords
		{
			{ position[0].x, position[0].y, m_Position.z },
			{ 0, 0, 0 },
			{ m_Color.r, m_Color.g, m_Color.g, m_Color.a },
			{ m_TexCoords.x, m_TexCoords.y }
		},
		{
			{ position[0].x, position[1].y, m_Position.z },
			{ 0, 0, 0 },
			{ m_Color.r, m_Color.g, m_Color.g, m_Color.a },
			{ m_TexCoords.x, m_TexCoords.w }
		},
		{
			{ position[1].x, position[1].y, m_Position.z },
			{ 0, 0, 0 },
			{ m_Color.r, m_Color.g, m_Color.g, m_Color.a },
			{ m_TexCoords.z, m_TexCoords.w }
		},
		{
			{ position[1].x, position[0].y, m_Position.z },
			{ 0, 0, 0 },
			{ m_Color.r, m_Color.g, m_Color.g, m_Color.a },
			{ m_TexCoords.z, m_TexCoords.y }
		},
	};
}

void Sprite::update()
{
	m_Vertices.setData(generateVertexData());
	m_HasChanged = false;
}
