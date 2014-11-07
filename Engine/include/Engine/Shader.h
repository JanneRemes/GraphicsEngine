
#ifndef SHADER_H
#define SHADER_H

#include <glew/glew.h>
#include <string>

class Shader final
{
	bool validateShader(GLuint shader);
	bool validateProgram(GLuint program);
public:
	static const std::string DefaultVertex;
	static const std::string DefaultFragment;

	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	Shader(const Shader& other) = default;
	~Shader();

	bool init(const std::string& vertexPath, const std::string& fragmentPath);

	GLuint getProgram() const;
private:
	bool m_IsInitialized = false;
	GLuint m_VertexShader = 0;
	GLuint m_FragmentShader = 0;
	GLuint m_Program = 0;
};

#endif // Include guard
