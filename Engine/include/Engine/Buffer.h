
#ifndef BUFFER_H
#define BUFFER_H

#include <glew/glew.h>
#include <vector>

template<typename T>
class Buffer
{
public:
	Buffer(GLuint size, GLenum target, GLenum usage);
	virtual ~Buffer();

	void update();
	void reserve(size_t newSize);
	void append(const std::vector<T>& data);
	void clear();

	GLuint getId() const;
	const GLuint getSize() const;
	const T* getData() const;

	const GLuint TypeSize;
	const GLuint Size;
	const GLenum Target;
	const GLenum Usage;
protected:
	GLuint m_BufferId = -1;
	std::vector<T> m_Buffer;
};

template<typename T>
Buffer<T>::Buffer(GLuint size, GLenum target, GLenum usage)
	: TypeSize(sizeof(T))
	, Size(size)
	, Target(target)
	, Usage(usage)
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(Target, m_BufferId);
	glBufferData(Target, 0, nullptr, Usage);
	glBindBuffer(Target, 0);
}

template<typename T>
Buffer<T>::~Buffer()
{
	glDeleteBuffers(1, &m_BufferId);
};

template<typename T>
void Buffer<T>::update()
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(Target, m_BufferId);
	glBufferSubData(Target, 0, m_Buffer.size(), m_Buffer.data());
	glBindBuffer(Target, 0);
}

template<typename T>
void Buffer<T>::reserve(size_t newSize)
{
	m_Buffer.reserve(newSize);
}

template<typename T>
void Buffer<T>::append(const std::vector<T>& data)
{
	if ((Size > 1) && (data.size() % Size > 0))
	{
		std::fprintf(stderr, "Error: Incomplete buffer data.\n");
		return;
	}

	m_Buffer.reserve(m_Buffer.size() + data.size());

	for (const auto& e : data)
	{
		m_Buffer.push_back(e);
	}
}

template<typename T>
void Buffer<T>::clear()
{
	m_Buffer.clear();
}

template<typename T>
GLuint Buffer<T>::getId() const
{
	return m_BufferId;
}

template<typename T>
const GLuint Buffer<T>::getSize() const
{
	return m_Buffer.size();
}

template<typename T>
const T* Buffer<T>::getData() const
{
	return m_Buffer.data();
}

#endif // Include guard
