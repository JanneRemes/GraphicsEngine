
#include <Engine/Engine.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IndexBuffer.h"
#include "VertexBuffer.h"

int main()
{
	const glm::ivec2 wndSize(1280, 720);
	Window wnd(wndSize, L"Test3");
	Context ctx(wnd);
	Event e;

	/**/
	VertexBuffer vb(VertexFormat::Position3f_Color4f_UV2f,
	{
		
	});

	IndexBuffer ib(
	{
		0
	});
	/**/

	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	GLuint program = shader.getProgram();

	shader.bind();
		Texture texture;
		texture.fromFile("test.png");
	shader.unbind();

	std::vector<GLfloat> vertices
	{
		/**/ -0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  1.0f,
		/**/ -0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  0.0f,
		/**/  0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  0.0f,
		/**/  0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  1.0f,
																		 	    
		/**/  0.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  1.0f,
		/**/  0.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  1.0f,  0.0f,
		/**/  1.5f,  0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  0.0f,
		/**/  1.5f, -0.5f,  0.0f, /**/  1.0f,  1.0f,  1.0f,  1.0f, /**/  0.0f,  1.0f,
	};

	std::vector<GLuint> indices
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,
	};

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
				glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), vertices.data());
				glVertexAttribPointer(colorIndex,    4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), vertices.data() + 3);
				glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), vertices.data() + 7);

				texture.bind(0);
					glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
				texture.unbind();
			}
			shader.unbind();
		}
		ctx.swap();
	}
}
