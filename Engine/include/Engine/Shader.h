
#ifndef SHADER_H
#define SHADER_H

#include <wgl_core_2_1/wgl.h>
#include <glm/glm.hpp>
#include <string>

class Shader final
{
	bool getCompileStatus(GLuint shader);
	bool getLinkStatus(GLuint program);

	std::string getShaderInfoLog(GLuint shader);
	std::string getProgramInfoLog(GLuint program);

	bool init(const char* vertexSource, const char* fragmentSource);
	void deinit();
public:
	static const std::string DefaultVertex;
	static const std::string DefaultFragment;

	Shader() = default;
	Shader(const Shader& other) = default;
	~Shader();

	bool fromFile(const std::string& vertexPath, const std::string& fragmentPath);
	bool fromSource(const std::string& vertexSource, const std::string& fragmentSource);

	void bind();
	void unbind();
	void unbindImmidiate();

	GLint getUniformLocation(const std::string& name) const;
	void setUniform(GLuint location, const glm::mat4& mat, bool transpose);
	void setUniform(GLuint location, const glm::vec4& v);
	void setUniform(GLuint location, const glm::vec3& v);
	void setUniform(GLuint location, const glm::vec2& v);
	void setUniform(GLuint location, GLfloat f);
	void setUniform(GLuint location, GLint i);

	GLuint getProgram() const;
private:
	size_t m_BindCount = 0;
	bool m_IsInitialized = false;
	GLuint m_VertexShader = 0;
	GLuint m_FragmentShader = 0;
	GLuint m_Program = 0;
};

#endif // Include guard
