
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
#include <Engine/Math.h>
#include <Engine/SpriteBatch.h>
#include <Engine/AssetManager.h>
#include <glm/glm.hpp>

int main(int argc, char** argv)
{
	Window wnd({ 800, 600 }, "Title");
	Context::Init(wnd);

	AssetManager assets;

	assets.registerLoadFunc<Shader>([](const std::string& filepath) -> Asset*
	{
		Shader* newShader = new Shader;
		if (newShader->fromFile(filepath))
			return newShader;
		return nullptr;
	});

	assets.registerLoadFunc<Texture>([](const std::string& filepath) -> Asset*
	{
		Texture* newTexture = new Texture;
		if (newTexture->fromFile(filepath))
			return newTexture;
		return nullptr;
	});

	// Using VertexBuffer
	/**
	{
		VertexBuffer vertices(
		{
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
			{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ {  0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
			{ {  0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
		});

		IndexBuffer indices(
		{
			0, 1, 2,
			2, 3, 0,
		});

		auto texture = assets.load<Texture>("images\\test1.png");
		texture->bind();

		auto shader = assets.load<Shader>("shaders\\default.glsl");
		shader->setUniform(shader->getUniformLocation("Texture"), 0);

		while (wnd.isOpen())
		{
			gl::GetAllErrors();

			wnd.update();

			Context::Clear({ 0, 0, 0, 0 });

			vertices.bind();
			indices.bind();

			shader->bind();
			texture->bind();

			gl::DrawElements(gl::TRIANGLES, indices.getSize(), gl::UNSIGNED_INT, 0);

			shader->unbind();
			texture->unbind();

			vertices.unbind();
			indices.unbind();

			Context::Swap();
		}
	}
	/**/

	// Using Sprite
	/**
	auto shader = assets.load<Shader>("shaders\\default.glsl");
	shader->setUniform(shader->getUniformLocation("Texture"), 0);

	auto texture = assets.load<Texture>("images\\test1.png");

	const size_t count = 100;
	Sprite* sprites = new Sprite[count];
	for (size_t i = 0; i < count; i++)
	{
		const int square = (int)sqrtl(count);
		sprites[i].setPosition({ -0.1f * (square / 2) + 0.1f * (i % square), -0.1f * (square / 2) + 0.1f * (i / square), 0 });
		sprites[i].setSize({ 0.1f, 0.1f });
		sprites[i].setTexture(*texture);
	}
	
	while (wnd.isOpen())
	{
		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		for (size_t i = 0; i < count; i++)
			sprites[i].draw(*shader);

		Context::Swap();
	}
	/**/

	// Using SpriteBatch
	/**
	{
		auto shader = assets.load<Shader>("shaders\\default.glsl");
		shader->setUniform(shader->getUniformLocation("Texture"), 0);

		std::vector<Texture*> textures;
		textures.push_back(assets.load<Texture>("images\\test1.png"));
		textures.push_back(assets.load<Texture>("images\\test2.png"));
		textures.push_back(assets.load<Texture>("images\\test3.png"));
		textures.push_back(assets.load<Texture>("images\\test4.png"));

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
			batch.draw(*shader);
			batch.clear();

			Context::Swap();
		}
	}
	/**/
}
