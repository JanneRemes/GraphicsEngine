
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
#include <Engine/Math.h>
#include <Engine/SpriteBatch.h>
#include <Engine/AssetManager.h>
#include <Engine/Model.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	Window wnd({ 800, 600 }, "Title");
	Context::Init(wnd);

	glm::mat4 World(0);
	glm::mat4 View(0);
	glm::mat4 Projection(0);

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

	assets.registerLoadFunc<Model>([](const std::string& filepath) -> Asset*
	{
		Model* newModel = new Model;
		if (newModel->fromFile(filepath))
			return newModel;
		return nullptr;
	});

	// Using VertexBuffer
	/*
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

		auto texture = assets.load<Texture>("images/test0.png");
		texture->bind();

		auto shader = assets.load<Shader>("shaders/default.glsl");
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
	//*/

	// Using Sprite
	/*
	auto shader = assets.load<Shader>("shaders/default.glsl");
	shader->setUniform(shader->getUniformLocation("Texture"), 0);

	auto texture = assets.load<Texture>("images/test1.png");

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
	//*/
	
	// Using SpriteBatch
	/*
	{
		auto shader = assets.load<Shader>("shaders/default.glsl");
		shader->setUniform(shader->getUniformLocation("Texture"), 0);

		std::vector<Texture*> textures;
		textures.push_back(assets.load<Texture>("images/test1.png"));
		textures.push_back(assets.load<Texture>("images/test2.png"));
		textures.push_back(assets.load<Texture>("images/test3.png"));
		textures.push_back(assets.load<Texture>("images/test4.png"));

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
	//*/

	// Using Model
	//*
	{
		Model* model = assets.load<Model>("models/cube/cube.obj");

		if (model)
		{
			std::fprintf(stdout, "Info: The model was loaded successfully.\n");
		}
		else
		{
			std::fprintf(stderr, "Error: Unable to load model file\n");
			std::abort();
		}

		float angle = 0.0f;
		float turnRate = 50.0f;
		Projection = glm::perspective(90.0f, (float)(wnd.getSize().x) / wnd.getSize().y, 0.001f, 1000.0f);
		View = glm::translate(glm::vec3(0.0f, 0.0f, -50.0f)) * glm::rotate(25.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//World = glm::rotate(angle += turnRate, glm::vec3(0.0f, 1.0f, 0.0f));

		auto shader = assets.load<Shader>("shaders/default.glsl");
		shader->setUniform(shader->getUniformLocation("Texture"), 0);
		shader->setUniform(shader->getUniformLocation("Projection"), Projection, false);
		shader->setUniform(shader->getUniformLocation("View"), View, false);
		//shader->setUniform(shader->getUniformLocation("World"), World, false);

		clock_t before = clock();
		clock_t now;
		float delta;
		uint32_t delay;

		while (wnd.isOpen())
		{
			now = clock();
			delta = (now - before) / static_cast<float>(CLOCKS_PER_SEC);
			before = now;

			wnd.update();

			World = glm::rotate(angle += turnRate * delta, glm::vec3(0.0f, 1.0f, 0.0f));
			shader->setUniform(shader->getUniformLocation("World"), World, false);

			Context::Clear({ 0, 0, 0, 0 });

			model->draw(*shader, assets);

			Context::Swap();

			gl::GetAllErrors();
		}
	}
	//*/
}
