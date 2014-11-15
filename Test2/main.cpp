
#include <Engine/Engine.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const GLfloat FloorVertices[] =
{
	// Front left
	-3.0f, 0.0f, 3.0f,
	0.0f, 0.0f, 0.0f,

	// Front right
	3.0f, 0.0f, 3.0f,
	0.0f, 0.0f, 0.0f,

	// Back left
	-3.0f, 0.0f, -3.0f,
	0.0f, 0.0f, 0.0f,

	// Back right
	3.0f, 0.0f, -3.0f,
	0.0f, 0.0f, 0.0f
};

static const GLfloat WallVertices[] =
{
	// Bottom left
	-2.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	// Bottom right
	2.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	// Top left
	-2.0f, 4.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	// top right
	2.0f, 4.0f, 0.0f,
	0.0f, 1.0f, 1.0f
};

static const GLuint FloorIndices[] =
{
	0u, 1u, 2u,
	2u, 1u, 3u
};

static const GLsizei FloorStride = 6 * sizeof(float);
static const GLsizei FloorColorOffset = 3;
static const GLsizei FloorIndexCount = 2 * 3;

int main()
{
	const glm::ivec2 wndSize(1280, 720);
	Window wnd(wndSize, L"Test2");
	Event e;

	ContextSettings settings;
	settings.ColorBits = 32;
	settings.DepthBits = 24;
	settings.StencilBits = 8;
	settings.AntialiasLevel = 16;
	Context ctx(wnd, settings);

	Shader shader;
	shader.fromFile("default.vert", "default.frag");
	GLuint program = shader.getProgram();

	// Enable attribute arrays
	const GLint positionIndex = glGetAttribLocation(program, "Position");
	glEnableVertexAttribArray(positionIndex);

	const GLint colorIndex = glGetAttribLocation(program, "Color");
	glEnableVertexAttribArray(colorIndex);

	{
		glUseProgram(program);

		// Projection
		{
			const glm::mat4 projectionTransform = glm::perspective(60.0f, static_cast<float>(wndSize.x) / wndSize.y, 0.01f, 1000.0f);
			const GLint projectionIndex = glGetUniformLocation(program, "Projection");
			glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projectionTransform));
		}

		// View
		{
			const glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, -2.0f, -10.0f)) * glm::rotate(-30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			const GLint viewIndex = glGetUniformLocation(program, "View");
			glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(viewTransform));
		}

		glUseProgram(0);
	}

	// World
	const GLint worldIndex = glGetUniformLocation(program, "World");
	glm::mat4 worldTransform;
	float angle = 0.0f;

	const GLint alphaIndex = glGetUniformLocation(program, "Alpha");

	while (wnd.isOpen())
	{
		while (wnd.pollEvent(e))
		{
			if (e.type == Event::Closed)
				wnd.close();
		}

		glStencilMask(0xFF);
		ctx.clear({ 1, 1, 1, 1 });

		glUseProgram(program);

		// Rotate the object
		angle += 1.0f;
		worldTransform = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(worldIndex, 1, GL_FALSE, glm::value_ptr(worldTransform));

		// Stencil setup
		{
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);
		}

		// Floor
		{
			glUniform1f(alphaIndex, 1.0f);

			glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, FloorStride, FloorVertices);
			glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, FloorStride, FloorVertices + FloorColorOffset);
			glDrawElements(GL_TRIANGLES, FloorIndexCount, GL_UNSIGNED_INT, FloorIndices);
		}

		// Stencil setup
		{
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_TRUE);
		}

		// Blend setup
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}

		// Reflection
		{
			glUniform1f(alphaIndex, 0.20f);

			worldTransform = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(1.0f, -1.0f, 1.0f));
			glUniformMatrix4fv(worldIndex, 1, GL_FALSE, glm::value_ptr(worldTransform));

			glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, FloorStride, WallVertices);
			glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, FloorStride, WallVertices + FloorColorOffset);

			glDrawElements(GL_TRIANGLES, FloorIndexCount, GL_UNSIGNED_INT, FloorIndices);
		}

		// Disable blend
		{
			glDisable(GL_BLEND);
		}

		// Disable stencil testing
		{
			glDisable(GL_STENCIL_TEST);
		}

		// Wall
		{
			glUniform1f(alphaIndex, 1.0f);

			worldTransform = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(worldIndex, 1, GL_FALSE, glm::value_ptr(worldTransform));

			glDrawElements(GL_TRIANGLES, FloorIndexCount, GL_UNSIGNED_INT, FloorIndices);
		}

		glUseProgram(0);

		ctx.swap();
	}
}
