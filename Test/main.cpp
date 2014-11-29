
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/Shader.h>
#include <Engine/Texture.h>
#include <glm/glm.hpp>
#include <Engine/Math.h>

class Sprite
{
public:
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

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	gl::GenBuffers(1, &vbo);

	// Create an element array
	GLuint ebo;
	gl::GenBuffers(1, &ebo);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), gl::DYNAMIC_DRAW);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), gl::DYNAMIC_DRAW);

	gl::EnableVertexAttribArray(gl::Position.Location);
	gl::VertexAttribPointer(gl::Position.Location, 2, gl::FLOAT, false, 7 * sizeof(float), 0);

	gl::EnableVertexAttribArray(gl::Color.Location);
	gl::VertexAttribPointer(gl::Color.Location, 3, gl::FLOAT, false, 7 * sizeof(float), (void*)(2 * sizeof(float)));

	gl::EnableVertexAttribArray(gl::UV.Location);
	gl::VertexAttribPointer(gl::UV.Location, 2, gl::FLOAT, false, 7 * sizeof(float), (void*)(5 * sizeof(float)));

	Shader shader;
	shader.fromFile("default.vert", "default.frag");

	GLint uniloc_Texture = gl::GetUniformLocation(shader.getProgram(), "Texture");
	shader.setUniform(uniloc_Texture, 0);

	Texture texture;
	texture.fromFile("test.png");

	while (wnd.isOpen())
	{
		wnd.update();

		Context::Clear({ 0, 0, 0, 0 });

		shader.bind();
		texture.bind();

		gl::DrawElements(gl::TRIANGLES, indices.size(), gl::UNSIGNED_INT, 0);

		texture.unbind();
		shader.unbind();

		Context::Swap();
	}

	gl::DeleteBuffers(1, &vbo);
	gl::DeleteBuffers(1, &ebo);
}
