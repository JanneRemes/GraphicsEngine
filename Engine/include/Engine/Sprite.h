
#ifndef SPRITE_H
#define SPRITE_H

#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>

class Sprite
{
public:
	Sprite() = default;
	Sprite(const glm::vec3& position, const glm::vec2& size, Texture& texture);

	void setPosition(const glm::vec3& position);

	void setSize(const glm::vec2& size);

	void setRotation(float rotation);

	void setColor(const glm::vec4& color);

	void setTexCoords(const glm::vec2& from, const glm::vec2& to);

	void setTexture(Texture& texture);

	void draw(Shader& shader);
private:
	void update();

	glm::vec3 m_Position = { 0, 0, 0 };
	glm::vec2 m_Size = { 1, 1 };
	float m_Rotation = { 0 };
	glm::vec4 m_Color = { 1, 1, 1, 1 };
	glm::vec4 m_TexCoords = { 0, 1, 1, 0 };

	bool m_HasChanged = true;
	Texture* m_Texture = nullptr;
	VertexBuffer m_Vertices;
	IndexBuffer m_Indices = { { 0, 1, 2, 2, 3, 0 } };
};

#endif // Include guard
