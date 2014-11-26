
#include <iostream>
#include <vector>

#include <Engine/Shader.h>
#include <Engine/Util.h>
#include <Engine/Graphics.h>

#ifdef GLSL
#error 'GLSL' already defined
#else
#define GLSL(source) "#version 150 core\n" #source

const std::string Shader::DefaultVertex = GLSL
(
	uniform mat4 ModelViewProjection;
	in      vec3 Position;
	in      vec4 Color;
	in      vec3 Normal;
	in      vec4 UV;
	out     vec4 FragColor;

	void main()
	{
		FragColor = Color;
		gl_Position = ModelViewProjection * vec4(Position, 1.0);
	}
);

const std::string Shader::DefaultFragment = GLSL
(
	in  vec4 FragColor;
	out vec4 FinalColor;

	void main()
	{
		FinalColor = FragColor;
	}
);

#undef GLSL
#endif

/*
	PRIVATE
*/
bool Shader::validateShader(GLuint shader)
{
	GLint logLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 1)
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

	if (logLength > 1)
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
Shader::~Shader()
{
	glDetachShader(m_Program, m_FragmentShader);
	glDetachShader(m_Program, m_VertexShader);
	glDeleteShader(m_FragmentShader);
	glDeleteShader(m_VertexShader);
	glDeleteProgram(m_Program);
}

bool Shader::fromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;

	if (!Util::ReadTextFile(vertexPath, vertexSource) ||
		!Util::ReadTextFile(fragmentPath, fragmentSource))
	{
		return false;
	}

	return init(vertexSource.c_str(), fragmentSource.c_str());
}

bool Shader::fromSource(const std::string& vertexSource, const std::string& fragmentSource)
{
	return init(vertexSource.c_str(), fragmentSource.c_str());
}

bool Shader::init(const char* vertexSource, const char* fragmentSource)
{
	if (m_IsInitialized)
	{
		std::cerr << "Error: Attempted to initialize Shader twice! Create new a shader instead.\n";
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
	glBindAttribLocation(m_Program, Graphics::Position.Location, Graphics::Position.Name);
	glBindAttribLocation(m_Program, Graphics::Color.Location,    Graphics::Color.Name);
	glBindAttribLocation(m_Program, Graphics::Normal.Location,   Graphics::Normal.Name);
	glBindAttribLocation(m_Program, Graphics::UV.Location,       Graphics::UV.Name);
	glLinkProgram(m_Program);
	if (!validateProgram(m_Program))
	{
		return false;
	}

	m_IsInitialized = true;
	return true;
}

void Shader::bind() const
{
	glUseProgram(m_Program);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

GLuint Shader::getProgram() const
{
	return m_Program;
}
