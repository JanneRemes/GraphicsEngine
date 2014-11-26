
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glew/glew.h>
#include <glew/wglew.h>
#include <glm/glm.hpp>
#include <string>

struct VertexAttribute
{
	unsigned int Location;
	unsigned int Size;
	char* Name;	
};

class Graphics
{
public:
	static VertexAttribute Position;
	static VertexAttribute Color;
	static VertexAttribute Normal;
	static VertexAttribute UV;
};

class GL
{
	inline static void CheckErrors()
	{
#ifdef _DEBUG
		unsigned int error;

		while ((error = glGetError()) != GL_NO_ERROR)
		{
			switch (error)
			{
			case GL_INVALID_ENUM:					std::fprintf(stdout, "Error: %s\n", "GL_INVALID_ENUM"); std::abort();
			case GL_INVALID_VALUE:					std::fprintf(stdout, "Error: %s\n", "GL_INVALID_VALUE"); std::abort();
			case GL_INVALID_OPERATION:				std::fprintf(stdout, "Error: %s\n", "GL_INVALID_OPERATION"); std::abort();
			case GL_STACK_OVERFLOW:					std::fprintf(stdout, "Error: %s\n", "GL_STACK_OVERFLOW"); std::abort();
			case GL_STACK_UNDERFLOW:				std::fprintf(stdout, "Error: %s\n", "GL_STACK_UNDERFLOW"); std::abort();
			case GL_OUT_OF_MEMORY:					std::fprintf(stdout, "Error: %s\n", "GL_OUT_OF_MEMORY"); std::abort();
			case GL_INVALID_FRAMEBUFFER_OPERATION:	std::fprintf(stdout, "Error: %s\n", "GL_INVALID_FRAMEBUFFER_OPERATION"); std::abort();
			case GL_TABLE_TOO_LARGE:				std::fprintf(stdout, "Error: %s\n", "GL_TABLE_TOO_LARGE"); std::abort();
			}
		}
#endif
	}
public:
	enum class BufferBindingTarget : unsigned int
	{
		ARRAY_BUFFER              = GL_ARRAY_BUFFER,              // Vertex attributes
		ATOMIC_COUNTER_BUFFER     = GL_ATOMIC_COUNTER_BUFFER,     // Atomic counter storage
		COPY_READ_BUFFER          = GL_COPY_READ_BUFFER,          // Buffer copy source
		COPY_WRITE_BUFFER         = GL_COPY_WRITE_BUFFER,         // Buffer copy destination
		DISPATCH_INDIRECT_BUFFER  = GL_DISPATCH_INDIRECT_BUFFER,  // Indirect compute dispatch commands
		DRAW_INDIRECT_BUFFER      = GL_DRAW_INDIRECT_BUFFER,      // Indirect command arguments
		ELEMENT_ARRAY_BUFFER      = GL_ELEMENT_ARRAY_BUFFER,      // Vertex array indices
		PIXEL_PACK_BUFFER         = GL_PIXEL_PACK_BUFFER,         // Pixel read target
		PIXEL_UNPACK_BUFFER       = GL_PIXEL_UNPACK_BUFFER,       // Texture data source
		QUERY_BUFFER              = GL_QUERY_BUFFER,              // Query result buffer
		SHADER_STORAGE_BUFFER     = GL_SHADER_STORAGE_BUFFER,     // Read-write storage for shaders
		TEXTURE_BUFFER            = GL_TEXTURE_BUFFER,            // Texture data buffer
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER, // Transform feedback buffer
		UNIFORM_BUFFER            = GL_UNIFORM_BUFFER,            // Uniform block storage
	};

	enum class BufferUsage : unsigned int
	{
		STREAM_DRAW  = GL_STREAM_DRAW,  // One write, few reads. Modified by application, used for drawing.
		STREAM_READ  = GL_STREAM_READ,  // One write, few reads. Modified by GL, read by the application.
		STREAM_COPY  = GL_STREAM_COPY,  // One write, few reads. Modified by GL, used for drawing.
		STATIC_DRAW  = GL_STATIC_DRAW,  // One write, many reads. Modified by application, used for drawing.
		STATIC_READ  = GL_STATIC_READ,  // One write, many reads. Modified by GL, read by the application.
		STATIC_COPY  = GL_STATIC_COPY,  // One write, many reads. Modified by GL, used for drawing.
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW, // Many writes, many reads. Modified by application, used for drawing.
		DYNAMIC_READ = GL_DYNAMIC_READ, // Many writes, many reads. Modified by GL, read by the application.
		DYNAMIC_COPY = GL_DYNAMIC_COPY, // Many writes, many reads. Modified by GL, used for drawing.
	};

	enum class Type : unsigned int
	{
		BYTE           = GL_BYTE,
		UNSIGNED_BYTE  = GL_UNSIGNED_BYTE,
		BOOL           = GL_BOOL,
		SHORT          = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT            = GL_INT,
		UNSIGNED_INT   = GL_UNSIGNED_INT,
		FLOAT          = GL_FLOAT,
		DOUBLE         = GL_DOUBLE,
	};

	enum class Mode : unsigned int
	{
		POINTS                   = GL_POINTS,
		LINE_STRIP               = GL_LINE_STRIP,
		LINE_LOOP                = GL_LINE_LOOP,
		LINES                    = GL_LINES,
		LINE_STRIP_ADJACENCY     = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY          = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP           = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN             = GL_TRIANGLE_FAN,
		TRIANGLES                = GL_TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY      = GL_TRIANGLES_ADJACENCY,
		PATCHES                  = GL_PATCHES,
	};

	static int ChoosePixelFormat(HDC device, const PIXELFORMATDESCRIPTOR& pfd)
	{
		return ::ChoosePixelFormat(device, &pfd);
	}

	static int SetPixelFormat(HDC device, int format, const PIXELFORMATDESCRIPTOR& pfd)
	{
		bool result = ::SetPixelFormat(device, format, &pfd) == TRUE;
		return result;
	}

	static HGLRC CreateContext(HDC device)
	{
		return wglCreateContext(device); CheckErrors();
	}

	static bool MakeCurrent(HDC device, HGLRC render)
	{
		bool result = wglMakeCurrent(device, render) == TRUE; CheckErrors();
		return result;
	}

	static void ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a); CheckErrors();
	}

	static void ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a); CheckErrors();
	}

	static void Clear(unsigned int bits)
	{
		glClear(bits); CheckErrors();
	}

	static unsigned int GenVertexArray()
	{
		unsigned int array;
		glGenVertexArrays(1, &array); CheckErrors();
		return array;
	}

	static unsigned int GenBuffer()
	{
		unsigned int buffer;
		glGenBuffers(1, &buffer); CheckErrors();
		return buffer;
	}

	static void DeleteVertexArray(unsigned int array)
	{
		glDeleteVertexArrays(1, &array); CheckErrors();
	}

	static void DeleteBuffer(unsigned int buffer)
	{
		glDeleteBuffers(1, &buffer); CheckErrors();
	}

	static void BindVertexArray(unsigned int array)
	{
		glBindVertexArray(array); CheckErrors();
	}

	static void BindBuffer(BufferBindingTarget target, unsigned int buffer)
	{
		glBindBuffer(static_cast<unsigned int>(target), buffer); CheckErrors();
	}

	static void BufferData(BufferBindingTarget target, int size, void* data, BufferUsage usage)
	{
		glBufferData(static_cast<unsigned int>(target), size, data, static_cast<unsigned int>(usage)); CheckErrors();
	}

	static void BufferSubData(BufferBindingTarget target, int offset, int size, void* data)
	{
		glBufferSubData(static_cast<unsigned int>(target), offset, size, data); CheckErrors();
	}

	static void EnableVertexAttribArray(unsigned int index)
	{
		glEnableVertexAttribArray(index); CheckErrors();
	}

	static void VertexAttribPointer(unsigned int index, int size, Type type, bool normalized, int stride, const void* pointer)
	{
		glVertexAttribPointer(index, size, static_cast<unsigned int>(type), normalized, stride, pointer); CheckErrors();
	}

	static void DrawElements(Mode mode, int count, Type type, const void* indices)
	{
		glDrawElements(static_cast<unsigned int>(mode), count, static_cast<unsigned int>(type), indices);
	}
};

#endif // Include guard
