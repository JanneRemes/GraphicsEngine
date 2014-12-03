
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
//#include <Engine/SpriteBatch.h>
#include <glm/glm.hpp>
#include <Engine/Math.h>
#include <array>

/**
#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>

class Sprite
{
public:
	void setPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void setPosition()
	{

	}

	void setPosition()
	{

	}

	void setPosition()
	{

	}

	void draw(Shader& shader)
	{
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
private:
	void update()
	{
		m_HasChanged = false;


	}

	glm::vec3 Position;
	glm::vec2 Size;
	float Rotation;
	glm::vec4 Color;
	glm::vec4 UV;

	bool m_HasChanged = true;
	Texture* m_Texture = nullptr;
	VertexBuffer m_Vertices;
	IndexBuffer m_Indices;
};
/**/

#include <Engine/Sprite.h>
#include <chrono>

int FindSquare(int start, int maxOffset = -1)
{
	int offset = 0;

	while (true)
	{
		if ((start + offset > 0))
		{
			const double square = sqrt(start + offset);

			if ((double)(square) - (int)(square) == 0.0)
				return start + offset;
		}

		if ((start - offset > 0))
		{
			double square = sqrt(start - offset);

			if ((double)(square) - (int)(square) == 0.0)
				return start - offset;
		}

		if ((maxOffset == -1) || (offset > maxOffset))
			offset++;
	}
}

int GetTimeDiff()
{
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::microseconds us;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	
	static auto before = Time::now();

	auto now = Time::now();
	auto delta = std::chrono::duration_cast<ms>(now - before);
	before = now;

	return (int)delta.count();
}

int main()
{
	Window wnd({ 800, 600 }, "Title");
	Context::Init(wnd);

	/**

	VertexBuffer vertices(
	{
		{ { -0.5f, -0.5f,  0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
		{ { -0.5f,  0.5f,  0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
		{ {  0.5f,  0.5f,  0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f,  0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
	});

	IndexBuffer indices
	({
		0, 1, 2,
		2, 3, 0,
	});

	vertices.bind();
	indices.bind();

	Shader shader;
	shader.fromFile("default.vert", "default.frag");

	const GLint uniloc_Texture = shader.getUniformLocation("Texture");
	shader.setUniform(uniloc_Texture, 0);

	Texture texture;
	texture.fromFile("test.png");

	while (wnd.isOpen())
	{
		gl::GetAllErrors();

		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		shader.bind();
		texture.bind();

		gl::DrawElements(gl::TRIANGLES, indices.getSize(), gl::UNSIGNED_INT, 0);

		texture.unbind();
		shader.unbind();

		Context::Swap();
	}

	/**/

	/**
	Shader shader;
	shader.fromFile("default.vert", "default.frag");

	Texture texture;
	texture.fromFile("test.png");

	GLint uTexLoc = shader.getUniformLocation("Texture");

	shader.setUniform(uTexLoc, 0);

	SpriteBatch batch(10);

	Sprite s1;
	s1.Position = { 0, 0, 0 };
	s1.Size = { 1, 1 };
	s1.Rotation = { 0 };
	s1.Color = { 1, 1, 1, 1 };
	s1.TexCoords[0] = { 0, 1 };
	s1.TexCoords[1] = { 1, 0 };

	while (wnd.isOpen())
	{
		gl::GetAllErrors();

		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		batch.Begin(&texture, &shader);
		{
			batch.Draw(s1);
		}
		batch.End();

		Context::Swap();
	}
	/**/

	/**
	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	shader.setUniform(shader.getUniformLocation("Texture"), 0);

	Texture texture;
	texture.fromFile("test.png");

	const size_t count = FindSquare(100);
	std::printf("count = %d\n", count);

	Sprite* sprites = new Sprite[count];
	for (size_t i = 0; i < count; i++)
	{
		const int square = (int)sqrtl(count);
		sprites[i].setPosition({ -0.1f * (square / 2) + 0.1f * (i % square), -0.1f * (square / 2) + 0.1f * (i / square), 0 });
		sprites[i].setSize({ 0.1f, 0.1f });
		sprites[i].setTexture(texture);
	}
	
	while (wnd.isOpen())
	{
		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		for (size_t i = 0; i < count; i++)
			sprites[i].draw(shader);

		Context::Swap();
	}
	/**/
}
