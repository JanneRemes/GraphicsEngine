
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

	bool fromData(const std::vector<char>& png);
	
	bool fromFile(const std::string& filepath);

	void setSmooth(bool b);

	GLuint getId() const;
private:
	GLuint m_TextureId = 0;
};

#endif // Include guard
