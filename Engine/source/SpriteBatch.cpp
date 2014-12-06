
#include <Engine/SpriteBatch.h>

void SpriteBatch::add(const Sprite& sprite)
{
	auto& indices = m_Indices[sprite.getTexture()];
	const size_t index = m_Vertices.size();
	auto newIndices =
	{
		index + 0, index + 1, index + 2,
		index + 2, index + 3, index + 0
	};
	indices.insert(indices.end(), newIndices.begin(), newIndices.end());

	auto newVertices = sprite.generateVertexData();
	m_Vertices.insert(m_Vertices.end(), newVertices.begin(), newVertices.end());
}

void SpriteBatch::draw(Shader& shader)
{
	m_VertexBuffer.setData(m_Vertices);
	m_VertexBuffer.bind();
	shader.bind();

	for (const auto& pair : m_Indices)
	{
		m_IndexBuffer.setData(pair.second);
		m_IndexBuffer.bind();

		if (pair.first != nullptr)
		{
			pair.first->bind();
			gl::DrawElements(gl::TRIANGLES, pair.second.size(), gl::UNSIGNED_INT, 0);
			pair.first->unbind();
		}
		else
		{
			gl::DrawElements(gl::TRIANGLES, pair.second.size(), gl::UNSIGNED_INT, 0);
		}
	}

	shader.unbind();
	m_IndexBuffer.unbind();
	m_VertexBuffer.unbind();
}

void SpriteBatch::clear()
{
	m_Vertices.clear();
	m_Indices.clear();
}
