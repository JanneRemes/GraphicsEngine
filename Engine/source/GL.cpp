
#include <Engine/GL.h>
#include <iostream>

namespace gl
{
	void GetAllErrors()
	{
		GLenum error;

		while ((error = gl::GetError()) != gl::NO_ERROR_)
		{
			switch (error)
			{
			case gl::INVALID_ENUM:      std::fprintf(stderr, "Error: %s\n", "INVALID_ENUM");      break;
			case gl::INVALID_VALUE:     std::fprintf(stderr, "Error: %s\n", "INVALID_VALUE");     break;
			case gl::INVALID_OPERATION: std::fprintf(stderr, "Error: %s\n", "INVALID_OPERATION"); break;
			case gl::STACK_OVERFLOW:    std::fprintf(stderr, "Error: %s\n", "STACK_OVERFLOW");    break;
			case gl::STACK_UNDERFLOW:   std::fprintf(stderr, "Error: %s\n", "STACK_UNDERFLOW");   break;
			case gl::OUT_OF_MEMORY:     std::fprintf(stderr, "Error: %s\n", "OUT_OF_MEMORY");     break;
			default:                    std::fprintf(stderr, "Error: %s\n", "UNKNOWN");           break;
			}
		}
	}
}