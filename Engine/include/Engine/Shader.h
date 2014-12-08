
#ifndef SHADER_H
#define SHADER_H

#include <wgl_core_2_1/wgl.h>
#include <glm/glm.hpp>
#include <Engine/Asset.h>

#define Shader_Delim_Vertex   "//<VERTEX"
#define Shader_Delim_Fragment "//<FRAGMENT"

class Shader final : public Asset
{
	static bool getCompileStatus(GLuint shader);
	static bool getLinkStatus(GLuint program);

	static std::string getShaderInfoLog(GLuint shader);
	static std::string getProgramInfoLog(GLuint program);

	bool init(const char* vertexSource, const char* fragmentSource);
	void deinit();
public:
	static const std::string DefaultVertex;
	static const std::string DefaultFragment;

	Shader() = default;
	Shader(const Shader& other) = default;
	Shader(const std::string& shaderPath);
	~Shader();

	bool fromFile(const std::string& shaderPath);
	bool fromFiles(const std::string& vertexPath, const std::string& fragmentPath);
	bool fromSource(const std::string& vertexSource, const std::string& fragmentSource);

	void bind();
	void unbind();
	void unbindImmediate();

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
