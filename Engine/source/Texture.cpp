
#include <Engine/Texture.h>


bool Texture::init(const unsigned char* png, size_t size)
{
	std::vector<unsigned char> pixels;
	size_t width, height;
	size_t error = lodepng::decode(pixels, width, height, png, size);

	if (error)
	{
		std::fprintf(stderr, "LodePNG error: %s\n", lodepng_error_text(error));
		return false;
	}

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

	return true;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureId);
}

bool Texture::fromData(const std::vector<char>& png)
{
	return init(reinterpret_cast<const unsigned char*>(png.data()), png.size());
}

bool Texture::fromFile(const std::string& filepath)
{
	std::vector<unsigned char> png;
	lodepng::load_file(png, filepath);
	return init(png.data(), png.size());
}

void Texture::setSmooth(bool b)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, b ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, b ? GL_LINEAR : GL_NEAREST);
}

GLuint Texture::getId() const
{
	return m_TextureId;
}
