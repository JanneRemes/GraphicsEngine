
#ifndef BUFFER_H
#define BUFFER_H

#include <wgl_core_2_1/wgl.h>
#include <vector>

template<class T>
class Buffer
{
public:
	Buffer(GLenum target, GLenum usage)
		: m_Target(target)
		, m_Usage(usage)
	{
		gl::GenBuffers(1, &m_Id);
		gl::BindBuffer(m_Target, m_Id);
		gl::BufferData(m_Target, 0, nullptr, m_Usage);
		gl::BindBuffer(m_Target, 0);
	}

	Buffer(GLenum target, const std::vector<T>& data, GLenum usage)
	{
		gl::GenBuffers(1, &m_Id);
		gl::BindBuffer(m_Target, m_Id);
		gl::BufferData(m_Target, data.size(), data.data(), m_Usage);
		gl::BindBuffer(m_Target, 0);
		m_Size = data.size();
	}

	virtual ~Buffer()
	{
		gl::DeleteBuffers(1, &m_Id);
	}

	void setData(const std::vector<T>& data)
	{
		gl::BindBuffer(m_Target, m_Id);
		gl::BufferData(m_Target, data.size(), data.data(), m_Usage);
		gl::BindBuffer(m_Target, 0);
		m_Size = data.size();
	}

	void setData(size_t offset, const std::vector<T>& data)
	{
		const GLintptr byteOffset = offset * sizeof(T);

		gl::BindBuffer(m_Target, m_Id);
		gl::BufferSubData(m_Target, byteOffset, data.size(), data.data());
		gl::BindBuffer(m_Target, 0);
	}

	virtual void bind()
	{
		gl::BindBuffer(m_Target, m_Id);
	}

	void unbind()
	{
		gl::BindBuffer(m_Target, 0);
	}

	size_t getSize() const
	{
		return m_Size;
	}

	GLuint getId() const
	{
		return m_Id;
	}
protected:
	size_t m_Size = 0;
	GLuint m_Id = 0;
	const GLenum m_Target;
	const GLenum m_Usage;
};

#endif // Include guard
