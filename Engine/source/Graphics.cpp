
#include <Engine/Graphics.h>

namespace gl
{

	void GetAllErrors()
	{
		GLenum error;

		while ((error = gl::GetError()) != gl::NO_ERROR_)
		{
			switch (error)
			{
			case gl::INVALID_ENUM:      std::printf("Error: %s\n", "INVALID_ENUM");      break;
			case gl::INVALID_VALUE:     std::printf("Error: %s\n", "INVALID_VALUE");     break;
			case gl::INVALID_OPERATION: std::printf("Error: %s\n", "INVALID_OPERATION"); break;
			case gl::STACK_OVERFLOW:    std::printf("Error: %s\n", "STACK_OVERFLOW");    break;
			case gl::STACK_UNDERFLOW:   std::printf("Error: %s\n", "STACK_UNDERFLOW");   break;
			case gl::OUT_OF_MEMORY:     std::printf("Error: %s\n", "OUT_OF_MEMORY");     break;
			default:                    std::printf("Error: %s\n", "UNKNOWN");           break;
			}

		}
	}

}