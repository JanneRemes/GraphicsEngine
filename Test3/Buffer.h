
#ifndef BUFFER_H
#define BUFFER_H

#define GLEW_STATIC
#include <glew/glew.h>
#include <vector>

template<typename T>
class Buffer
{
public:
	Buffer(GLuint size, GLenum target, GLenum usage)
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

	virtual ~Buffer() = 0 {}

	void update()
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(Target, m_BufferId);
		glBufferSubData(Target, 0, m_Buffer.size(), m_Buffer.data());
		glBindBuffer(Target, 0);
	}

	void append(const std::vector<T>& data)
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

	void clear()
	{
		m_Buffer.clear();
	}

	GLuint getId() const
	{
		return m_BufferId;
	}

	const GLuint getSize() const
	{
		return m_Buffer.size();
	}

	const T* getData() const
	{
		return m_Buffer.data();
	}

	const GLuint TypeSize;
	const GLuint Size;
	const GLenum Target;
	const GLenum Usage;
protected:
	GLuint m_BufferId = -1;
	std::vector<T> m_Buffer;
};

#endif // Include guard
