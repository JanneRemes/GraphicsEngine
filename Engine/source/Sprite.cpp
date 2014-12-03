
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

void Sprite::draw(Shader& shader)
{
	if (m_HasChanged)
		update();

	m_Vertices.bind();
	m_Indices.bind();
	shader.bind();

	if (m_Texture != nullptr)
		m_Texture->bind();

	gl::DrawElements(gl::TRIANGLES, m_Indices.getSize(), gl::UNSIGNED_INT, 0);

	if (m_Texture != nullptr)
		m_Texture->unbind();

	shader.unbind();
	m_Indices.unbind();
	m_Vertices.unbind();
}

void Sprite::update()
{
	const glm::vec2 position[2]
	{
		Math::Rotate(glm::vec2(m_Position) - m_Size * 0.5f, m_Rotation),
		Math::Rotate(glm::vec2(m_Position) + m_Size * 0.5f, m_Rotation),
	};

	m_Vertices.setData(
	{
		/*
			Position
			Normal
			Color
			TexCoords
		*/

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
	});

	m_HasChanged = false;
}
