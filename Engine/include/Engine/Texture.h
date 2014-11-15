
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew/glew.h>
#include <lodepng/lodepng.h>
#include <vector>

class Texture final
{
	bool init(const unsigned char* png, size_t size);

public:
	Texture() = default;
	~Texture();

	bool fromMemory(const std::vector<char>& png);
	bool fromFile(const std::string& filepath);

	void setSmooth(bool b);

	void bind(GLuint unit);
	void unbind();

	GLuint getUnit() const;
	GLuint getId() const;
private:
	GLuint m_Unit = -1;
	GLuint m_Id = -1;
};

#endif // Include guard
