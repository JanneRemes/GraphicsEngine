
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
#include <glm/glm.hpp>
#include <Engine/Math.h>

struct Sprite
{
	glm::vec2 Position;
	glm::vec4 Color;
	glm::vec4 UV;
	glm::vec2 Size;
	float Rotation;
	float Z;
	Texture* TexturePtr;

	std::vector<float> GetVertices() const
	{
		const glm::vec2 position = Math::Rotate(const_cast<const glm::vec2&>(Position), Rotation);
		const glm::vec2 size = Math::Rotate(const_cast<const glm::vec2&>(Size), Rotation);

		return
		{
			// Bottom left
			position.x, position.y, Z,
			Color.r, Color.g, Color.b, Color.a,
			UV.x, UV.y,

			// Top left
			position.x, position.y + size.y, Z,
			Color.r, Color.g, Color.b, Color.a,
			UV.x, UV.w,

			// Top right
			position.x + size.x, position.y + size.y, Z,
			Color.r, Color.g, Color.b, Color.a,
			UV.z, UV.w,

			// Bottom right
			position.x + size.x, position.y, Z,
			Color.r, Color.g, Color.b, Color.a,
			UV.z, UV.y,
		};
	}
};

int main()
{
	Window wnd({ 800, 600 }, "Title");
	Context::Init(wnd);

	std::vector<float> vertices
	{
		-0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
		-0.5f,  0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 0.0f, 0.0f,
		 0.5f,  0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f,
		 0.5f, -0.5f, /**/ 1.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f,
	};

	std::vector<unsigned int> indices
	{
		0, 1, 2,
		2, 3, 0,
	};

	// Create Vertex Array Object
	GLuint vao = GL::GenVertexArray();

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo = GL::GenBuffer();

	// Create an element array
	GLuint ebo = GL::GenBuffer();

	GL::BindVertexArray(vao);
	GL::BindBuffer(GL::BufferBindingTarget::ARRAY_BUFFER, vbo);
	GL::BufferData(GL::BufferBindingTarget::ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL::BufferUsage::DYNAMIC_DRAW);
	GL::BindBuffer(GL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER, ebo);
	GL::BufferData(GL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL::BufferUsage::DYNAMIC_DRAW);

	GL::EnableVertexAttribArray(Graphics::Position.Location);
	GL::VertexAttribPointer(Graphics::Position.Location, 2, GL::Type::FLOAT, false, 7 * sizeof(float), 0);

	GL::EnableVertexAttribArray(Graphics::Color.Location);
	GL::VertexAttribPointer(Graphics::Color.Location, 3, GL::Type::FLOAT, false, 7 * sizeof(float), (void*)(2 * sizeof(float)));

	GL::EnableVertexAttribArray(Graphics::UV.Location);
	GL::VertexAttribPointer(Graphics::UV.Location, 2, GL::Type::FLOAT, false, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	
	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	shader.bind();
	glUniform1i(glGetUniformLocation(shader.getProgram(), "Texture"), 0);
	shader.unbind();

	Texture texture;
	texture.fromFile("test.png");

	GL::BindVertexArray(0);

	while (wnd.isOpen())
	{
		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		GL::BindVertexArray(vao);
		shader.bind();
		texture.bind(0);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		texture.unbind();
		shader.unbind();
		GL::BindVertexArray(0);

		Context::Swap();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
