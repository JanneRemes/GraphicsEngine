
#include <iostream>
#include <vector>

#include <Engine/Shader.h>
#include <Engine/Util.h>

static const std::string DefaultVertex =
"\n" "#version 150"
"\n"
"\n" "uniform mat4 u_ModelViewProjection;"
"\n" "in      vec3 i_Position;"
"\n" "in      vec4 i_Color;"
"\n" "in      vec4 i_UV;"
"\n" "out     vec4 o_Color;"
"\n"
"\n" "void main()"
"\n" "{"
"\n" "    o_Color = i_Color;"
"\n" "    gl_Position = u_ModelViewProjection * vec4(i_Position, 1.0);"
"\n" "}"
"\n";

static const std::string DefaultFragment =
"\n" "#version 150 core"
"\n"
"\n" "in  vec4 i_Color;"
"\n" "out vec4 o_Color;"
"\n"
"\n" "void main()"
"\n" "{"
"\n" "    o_Color = i_Color;"
"\n" "}"
"\n";

/*
	PRIVATE
*/
bool Shader::validateShader(GLuint shader)
{
	GLint logLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		std::vector<GLchar> log(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, log.data());
		std::cerr << log.data();

		return false;
	}

	return true;
}

bool Shader::validateProgram(GLuint program)
{
	GLint logLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		std::vector<GLchar> log(logLength);
		glGetProgramInfoLog(program, logLength, nullptr, log.data());
		std::cerr << log.data();

		return false;
	}

	return true;
}

/*
	PUBLIC
*/
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	init(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDetachShader(m_Program, m_FragmentShader);
	glDetachShader(m_Program, m_VertexShader);
	glDeleteShader(m_FragmentShader);
	glDeleteShader(m_VertexShader);
	glDeleteProgram(m_Program);
}

bool Shader::init(const std::string& vertexPath, const std::string& fragmentPath)
{
	if (m_IsInitialized)
	{
		std::cerr << "Error: Attempted to initialize Shader twice! Create new a shader instead.\n";
		return false;
	}

	char const* vertexSource = nullptr;
	char const* fragmentSource = nullptr;

	if (!Util::ReadTextFile(vertexPath, vertexSource) ||
		!Util::ReadTextFile(fragmentPath, fragmentSource))
	{
		return false;
	}

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
	glCompileShader(m_VertexShader);
	if (!validateShader(m_VertexShader))
	{
		return false;
	}

	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(m_FragmentShader);
	if (!validateShader(m_FragmentShader))
	{
		return false;
	}

	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);
	glLinkProgram(m_Program);
	if (!validateProgram(m_Program))
	{
		return false;
	}

	m_IsInitialized = true;
	return true;
}

GLuint Shader::getProgram() const
{
	return m_Program;
}
