
#ifndef BUFFER_H
#define BUFFER_H

#include <Engine/GLUtil.h>
#include <glew/glew.h>
#include <stdexcept>
#include <vector>

enum class BufferType : GLenum
{
	Vertex = GL_ARRAY_BUFFER,
	Index = GL_ELEMENT_ARRAY_BUFFER
};

enum class BufferUsage : GLenum
{
	StaticDraw = GL_STATIC_DRAW,
	DynamicDraw = GL_DYNAMIC_DRAW,
	StreamDraw = GL_STREAM_DRAW,

	StaticRead = GL_STATIC_READ,
	DynamicRead = GL_DYNAMIC_READ,
	StreamRead = GL_STREAM_READ,

	StaticCopy = GL_STATIC_COPY,
	DynamicCopy = GL_DYNAMIC_COPY,
	StreamCopy = GL_STREAM_COPY
};

struct BufferElement
{
	const size_t size;
	const std::string name;
	const GLint location;
	const bool normalized;

	BufferElement(size_t size, const std::string& name = "", GLuint location = -1, bool normalized = false)
		: size(size)
		, name(name)
		, location(location)
		, normalized(normalized)
	{
	}

	BufferElement(const BufferElement& other) = default;

	BufferElement& operator=(const BufferElement& other)
	{
		return *new (this) BufferElement(other);
	}
};

template<typename T>
class Buffer
{
	void applyElements(const std::vector<BufferElement>& elements)
	{
		for (const auto& e : elements)
		{
			m_Elements.emplace_back(e.size, e.name, e.location, e.normalized);
			m_ElementSize += e.size * m_TypeSize;
		}

		// If this is a IndexBuffer, skip the attribute setup
		if (m_BufferType == static_cast<GLenum>(BufferType::Index))
			return;

		size_t offset = 0;
		for (const auto& e : elements)
		{
			offset += e.size * m_TypeSize;

			if (e.location > -1)
			{
				glEnableVertexAttribArray(e.location);
				glVertexAttribPointer(e.location, e.size,
					GL::Scalar<T>(), GL::Bool(e.normalized),
					m_ElementSize, (void*)offset);
			}
		}
	}
public:
	Buffer(BufferType bufferType, BufferUsage bufferUsage, const std::vector<BufferElement>& elements)
		: m_BufferType(static_cast<GLenum>(bufferType))
		, m_BufferUsage(static_cast<GLenum>(bufferUsage))
		, m_TypeSize(sizeof(T))
		, m_ElementSize(0)
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(m_BufferType, m_BufferId);
		applyElements(elements);
		glBufferData(m_BufferType, 0, nullptr, m_BufferUsage);
		glBindBuffer(m_BufferType, 0);
	}

	Buffer(BufferType bufferType, BufferUsage bufferUsage, const std::vector<BufferElement>& elements, const std::vector<T>& values)
		: m_BufferType(static_cast<GLenum>(bufferType))
		, m_BufferUsage(static_cast<GLenum>(bufferUsage))
		, m_TypeSize(sizeof(T))
		, m_ElementSize(0)
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(m_BufferType, m_BufferId);
		applyElements(elements);
		glBufferData(m_BufferType, values.size() / m_ElementSize, values.data(), m_BufferUsage);
		glBindBuffer(m_BufferType, 0);
	}

	~Buffer()
	{
		glDeleteBuffers(1, &m_BufferId);
	}

	void setData(const std::vector<T>& values) const
	{
		glBindBuffer(m_BufferType, m_BufferId);
		glBufferSubData(m_BufferType, 0, values.size() / m_ElementSize, values.data());
		glBindBuffer(m_BufferType, 0);
	}

	void getId() const
	{
		return m_BufferId;
	}
private:
	const GLenum m_BufferType;
	const GLenum m_BufferUsage;
	const size_t m_TypeSize;

	GLuint m_BufferId;
	size_t m_ElementSize;
	std::vector<BufferElement> m_Elements;
};

#endif // Include guard
