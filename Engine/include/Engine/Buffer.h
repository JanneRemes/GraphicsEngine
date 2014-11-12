
#ifndef BUFFER_H
#define BUFFER_H

#include <stdexcept>
#include <glew/glew.h>
#include <vector>

template<typename T>
class Buffer
{
public:
	enum class Type
	{
		Vertex = GL_ARRAY_BUFFER,
		Index = GL_ELEMENT_ARRAY_BUFFER
	};

	struct Element
	{
		const size_t size;
		const std::string name;

		Element(size_t size, const std::string& name = "")
			: size(size)
			, name(name)
		{
		}
	};

	Buffer(Type bufferType, const std::vector<Element>& elements)
		: m_TypeSize(sizeof(T))
		, m_BufferType(type)
	{
		m_ElementSize = 0;
		for (const auto& e : elements)
		{
			m_Elements.emplace_back(amount, name);
			m_ElementSize += amount * m_TypeSize
		}

		GLenum type = getType(bufferType);
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(type, m_BufferId);
		glBufferData(type, 0, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(type, 0);
	}

	Buffer(Type bufferType, const std::vector<Element>& elements, const std::vector<T>& values)
		: m_TypeSize(sizeof(T))
		, m_BufferType(type)
	{
		m_ElementSize = 0;
		for (const auto& e : elements)
		{
			m_Elements.emplace_back(amount, name);
			m_ElementSize += amount * m_TypeSize
		}

		GLenum type = getType(bufferType);
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(type, m_BufferId);
		glBufferData(type, values.size() / m_ESize, values.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(type, 0);
	}

	~Buffer()
	{
		glDeleteBuffers(1, &m_BufferId);
	}

	void setData(const std::vector<T>& values)
	{
		glBindBuffer(type, m_BufferId);
		glBufferSubData(type, values.size() / m_ESize, values.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(type, 0);
	}

	void getId() const
	{
		return m_BufferId;
	}

	const std::string& getElementName(size_t index) const
	{
		return m_Elements[index];
	}
private:
	const Type m_Type;
	const size_t m_TypeSize;
	const size_t m_ElementSize;

	GLuint m_BufferId;
	std::vector<Element> m_Elements;
};

/*
	- EXAMPLE -

	Buffer<GLfloat> QuadVertices(BufferType::Vertex,
	{
		BufferElement(3, "Position"),
		BufferElement(4, "Color"),
		BufferElement(2, "UV")
	},
	{
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f
	});

	Buffer<GLuint> QuadIndices(BufferType::Index,
	{
		BufferElement(1)
	},
	{
		0, 2, 3,
		3, 1, 0 
	});
*/

#endif // Include guard
