
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
#include <Engine/Math.h>
#include <glm/glm.hpp>

#include <Engine/SpriteBatch.h>

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

	/**/
	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	shader.setUniform(shader.getUniformLocation("Texture"), 0);

	const auto loadTexture = [](const std::string& filename)
	{
		auto texture = new Texture;
		texture->fromFile(filename);
		return texture;
	};

	std::vector<Texture*> textures;
	textures.push_back(loadTexture("test1.png"));
	textures.push_back(loadTexture("test2.png"));
	textures.push_back(loadTexture("test3.png"));
	textures.push_back(loadTexture("test4.png"));

	const size_t count = 100;
	Sprite* sprites = new Sprite[count];
	for (size_t i = 0; i < count; i++)
	{
		const int square = (int)sqrtl(count);
		sprites[i].setPosition({ -0.1f * (square / 2) + 0.1f * (i % square), -0.1f * (square / 2) + 0.1f * (i / square), 0 });
		sprites[i].setSize({ 0.1f, 0.1f });
		sprites[i].setTexture(*(textures[i % 4]));
	}

	SpriteBatch batch;

	while (wnd.isOpen())
	{
		gl::GetAllErrors();

		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		for (size_t i = 0; i < count; i++)
			batch.add(sprites[i]);
		batch.draw(shader);
		batch.clear();

		Context::Swap();
	}

	for (auto& e : textures)
		delete e;
	/**/

	/**
	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	shader.setUniform(shader.getUniformLocation("Texture"), 0);

	Texture texture;
	texture.fromFile("test1.png");

	const size_t count = 100;
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
