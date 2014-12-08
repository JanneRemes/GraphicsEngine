
#ifndef TEXTURE_H
#define TEXTURE_H

#include <wgl_core_2_1/wgl.h>
#include <lodepng/lodepng.h>
#include <glm/glm.hpp>
#include <vector>

#include <Engine/Asset.h>

class Texture final : public Asset
{
	bool init(const unsigned char* png, size_t size);

public:
	Texture() = default;
	~Texture();

	bool fromMemory(const std::vector<char>& png);
	bool fromFile(const std::string& filepath);

	void setSmooth(bool b);

	void bind();
	void unbind();

	const glm::uvec2& getSize() const;

	GLuint getId() const;
private:
	glm::uvec2 m_Size;
	GLuint m_Id = 0;
};

#endif // Include guard
