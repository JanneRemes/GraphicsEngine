
#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <Engine/Sprite.h>
#include <map>

class SpriteBatch
{
public:
	void add(const Sprite& sprite);
	void draw(Shader& shader);
	void clear();
private:
	std::vector<Vertex> m_Vertices;
	std::map<Texture*, std::vector<GLuint>> m_Indices;
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
};

#endif // Include guard
