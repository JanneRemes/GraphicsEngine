
#include <Engine/Texture.h>

bool Texture::init(const unsigned char* png, size_t size)
{
	std::vector<unsigned char> pixels;
	size_t error = lodepng::decode(pixels, m_Size.x, m_Size.x, png, size);

	if (error)
	{
		std::fprintf(stderr, "LodePNG error: %s\n", lodepng_error_text(error));
		return false;
	}

	gl::GenTextures(1, &m_Id);
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_Id);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, m_Size.x, m_Size.x, 0, gl::RGBA, gl::UNSIGNED_BYTE, pixels.data());
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
	gl::BindTexture(gl::TEXTURE_2D, 0);

	return true;
}

Texture::~Texture()
{
	gl::DeleteTextures(1, &m_Id);
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
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_Id);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, b ? gl::LINEAR : gl::NEAREST);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, b ? gl::LINEAR : gl::NEAREST);
	gl::BindTexture(gl::TEXTURE_2D, 0);
}

void Texture::bind()
{
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_Id);
}

void Texture::unbind()
{
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, 0);
}

const glm::uvec2& Texture::getSize() const
{
	return m_Size;
}

GLuint Texture::getId() const
{
	return m_Id;
}
