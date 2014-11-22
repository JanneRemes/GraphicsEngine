
#include <Engine/Engine.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Engine/Util.h>

int main()
{
	const glm::ivec2 wndSize(1280, 720);
	Window wnd(wndSize, L"Test3");
	Context ctx(wnd);
	Event e;

	/**/
	VertexBuffer vertices(VertexFormat::Position3f_Color4f_UV2f);
		{
		vertices.append(
		{
			-0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  1.0f,
			-0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  0.0f,
			 0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  0.0f,
			 0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  1.0f,
		});

		vertices.append(
		{
			 0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  1.0f,
			 0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  0.0f,
			 1.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  0.0f,
			 1.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  1.0f,
		});

		vertices.append(
		{
			 1.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  1.0f,
			 1.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  0.0f,
			 2.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  0.0f,
			 2.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  1.0f,
		});
	}

	IndexBuffer indices;
	{
		indices.append(
		{
			0, 1, 2,
			2, 3, 0,
		});

		indices.append(
		{
			4, 5, 6,
			6, 7, 4,
		});

		indices.append(
		{
			8, 9, 10,
			10, 11, 8,
		});
	}
	/**/

	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	GLuint program = shader.getProgram();

	Texture texture;
	texture.fromFile("test.png");

	GLuint positionIndex = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(positionIndex);

	GLuint colorIndex = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(colorIndex);

	GLint texCoordIndex = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(texCoordIndex);

	shader.bind();
	{
		const glm::mat4 projectionTransform = glm::perspective(90.0f, static_cast<float>(wndSize.x) / wndSize.y, 0.01f, 1000.0f);
		const GLint projectionIndex = glGetUniformLocation(program, "Projection");
		glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projectionTransform));


		const glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, 0.0f, -5.0f)) * glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		const GLint viewIndex = glGetUniformLocation(program, "View");
		glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(viewTransform));

		const glm::mat4 worldTransform = glm::mat4();
		const GLint worldIndex = glGetUniformLocation(program, "World");
		glUniformMatrix4fv(worldIndex, 1, GL_FALSE, glm::value_ptr(worldTransform));

		const GLint texIndex = glGetUniformLocation(program, "Tex");
		glUniform1i(texIndex, 0);

		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, vertices.Size, vertices.getData() + 0);
		glVertexAttribPointer(colorIndex,    4, GL_FLOAT, GL_FALSE, vertices.Size, vertices.getData() + 3);
		glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, vertices.Size, vertices.getData() + 7);
	}
	shader.unbind();

	while (wnd.isOpen())
	{
		while (wnd.pollEvent(e))
		{
			if (e.type == Event::Closed)
				wnd.close();
		}

		ctx.clear({ 1.0f, 1.0f, 1.0f, 1 });
		{
			shader.bind();
			{
				texture.bind(0);
				{
					glDrawElements(GL_TRIANGLES, indices.getSize(), GL_UNSIGNED_INT, indices.getData());
				}
				texture.unbind();
			}
			shader.unbind();
		}
		ctx.swap();
	}
}
