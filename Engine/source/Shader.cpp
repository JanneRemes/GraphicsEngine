
#include <iostream>
#include <vector>

#include <Engine/Shader.h>
#include <Engine/Util.h>
#include <Engine/Graphics.h>
#include <glm/gtc/type_ptr.hpp>

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
bool Shader::getCompileStatus(GLuint shader)
{
	GLint result = 0;
	gl::GetShaderiv(shader, gl::COMPILE_STATUS, &result);
	return result == gl::TRUE_;
}

bool Shader::getLinkStatus(GLuint program)
{
	GLint result = 0;
	gl::GetProgramiv(program, gl::LINK_STATUS, &result);
	return result == gl::TRUE_;
}

std::string Shader::getShaderInfoLog(GLuint shader)
{
	GLint logLength;
	gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &logLength);

	std::vector<GLchar> log(logLength);
	gl::GetShaderInfoLog(shader, logLength, nullptr, log.data());
	return std::string(log.begin(), log.end());
}

std::string Shader::getProgramInfoLog(GLuint program)
{
	GLint logLength;
	gl::GetShaderiv(program, gl::INFO_LOG_LENGTH, &logLength);

	std::vector<GLchar> log(logLength);
	gl::GetProgramInfoLog(program, logLength, nullptr, log.data());
	return std::string(log.begin(), log.end());
}

/*
	PUBLIC
*/
Shader::~Shader()
{
	deinit();
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
	if (m_Program != 0)
	{
		deinit();
	}

	m_VertexShader = gl::CreateShader(gl::VERTEX_SHADER);
	gl::ShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
	gl::CompileShader(m_VertexShader);
	if (!getCompileStatus(m_VertexShader))
	{
		std::cerr << getShaderInfoLog(m_VertexShader);
		deinit();
		return false;
	}

	m_FragmentShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	gl::ShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);
	gl::CompileShader(m_FragmentShader);
	if (!getCompileStatus(m_FragmentShader))
	{
		std::cerr << getShaderInfoLog(m_VertexShader);
		deinit();
		return false;
	}

	m_Program = gl::CreateProgram();
	gl::AttachShader(m_Program, m_VertexShader);
	gl::AttachShader(m_Program, m_FragmentShader);
	gl::BindAttribLocation(m_Program, gl::Position.Location, gl::Position.Name);
	gl::BindAttribLocation(m_Program, gl::Color.Location,    gl::Color.Name);
	gl::BindAttribLocation(m_Program, gl::Normal.Location,   gl::Normal.Name);
	gl::BindAttribLocation(m_Program, gl::UV.Location,       gl::UV.Name);
	gl::LinkProgram(m_Program);
	if (!getLinkStatus(m_Program))
	{
		std::cerr << getProgramInfoLog(m_VertexShader);
		deinit();
		return false;
	}

	m_IsInitialized = true;
	return true;
}

void Shader::deinit()
{
	gl::DetachShader(m_Program, m_FragmentShader);
	gl::DetachShader(m_Program, m_VertexShader);
	gl::DeleteShader(m_FragmentShader);
	gl::DeleteShader(m_VertexShader);
	gl::DeleteProgram(m_Program);

	m_FragmentShader = 0;
	m_VertexShader = 0;
	m_Program = 0;
}

void Shader::bind()
{
	m_BindCount++;
	if (m_BindCount == 1)
	{
		gl::UseProgram(m_Program);
	}
}

void Shader::unbind()
{
	m_BindCount--;
	if (m_BindCount == 0)
	{
		gl::UseProgram(0);
	}
}

void Shader::unbindImmidiate()
{
	m_BindCount = 0;
	gl::UseProgram(0);
}

void Shader::setUniform(GLuint location, const glm::mat4& mat, bool transpose)
{
	bind();
	gl::UniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat));
	unbind();
}

void Shader::setUniform(GLuint location, const glm::vec4& v)
{
	bind();
	gl::Uniform4fv(location, 1, glm::value_ptr(v));
	unbind();
}

void Shader::setUniform(GLuint location, const glm::vec3& v)
{
	bind();
	gl::Uniform3fv(location, 1, glm::value_ptr(v));
	unbind();
}

void Shader::setUniform(GLuint location, const glm::vec2& v)
{
	bind();
	gl::Uniform2fv(location, 1, glm::value_ptr(v));
	unbind();
}

void Shader::setUniform(GLuint location, GLfloat f)
{
	bind();
	gl::Uniform1f(location, f);
	unbind();
}

void Shader::setUniform(GLuint location, GLint i)
{
	bind();
	gl::Uniform1i(location, i);
	unbind();
}

GLuint Shader::getProgram() const
{
	return m_Program;
}
