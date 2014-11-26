
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

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}

bool Texture::fromMemory(const std::vector<char>& png)
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
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, b ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, b ? GL_LINEAR : GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(GLuint unit)
{
	static GLint MaxTexUnits = 0;

	if (MaxTexUnits == 0)
	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTexUnits);
		MaxTexUnits -= 1;
	}

	if ((unit < 0) || (unit > static_cast<GLuint>(MaxTexUnits)))
	{
		std::fprintf(stderr, "Error: %d is an invalid texture unit. Valid range is 0..%d\n", unit, MaxTexUnits);
		return;
	}

	m_Unit = unit;
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::unbind()
{
	if (m_Unit < 0)
	{
		std::fprintf(stderr, "Error: Attempted to unbind a Texture before binding it.\n");
		return;
	}

	glActiveTexture(GL_TEXTURE0 + m_Unit);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_Unit = -1;
}

GLuint Texture::getUnit() const
{
	return m_Unit;
}

GLuint Texture::getId() const
{
	return m_Id;
}
