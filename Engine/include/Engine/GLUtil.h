
#ifndef GLUTIL_H
#define GLUTIL_H

#include <glm/glm.hpp>
#include <glew/glew.h>
#include <glew/wglew.h>

namespace GL
{
	inline static GLboolean Bool(bool b)
	{
		return b ? GL_TRUE : GL_FALSE;
	}

	// inline GLenum GetScalar<T>()
	namespace
	{
		template<typename T>
		inline static GLenum Scalar()
		{
			static_assert(false, "Error: Invalid template argument.");
		}

		template<>
		inline static GLenum Scalar<bool>()
		{
			return GL_BOOL;
		}

		template<>
		inline static GLenum Scalar<int>()
		{
			return GL_INT;
		}

		template<>
		inline static GLenum Scalar<unsigned int>()
		{
			return GL_UNSIGNED_INT;
		}

		template<>
		inline static GLenum Scalar<float>()
		{
			return GL_FLOAT;
		}

		template<>
		inline static GLenum Scalar<double>()
		{
			return GL_DOUBLE;
		}
	};

	// inline GLenum GetVector<T>()
	namespace
	{
		template<typename T>
		inline static GLenum Vector()
		{
			static_assert(false, "Error: Invalid template argument.");
		}

		// - Bool
		template<>
		inline static GLenum Vector<glm::bvec2>()
		{
			return GL_BOOL_VEC2;
		}

		template<>
		inline static GLenum Vector<glm::bvec3>()
		{
			return GL_BOOL_VEC3;
		}

		template<>
		inline static GLenum Vector<glm::bvec4>()
		{
			return GL_BOOL_VEC4;
		}

		// - Int
		template<>
		inline static GLenum Vector<glm::ivec2>()
		{
			return GL_INT_VEC2;
		}

		template<>
		inline static GLenum Vector<glm::ivec3>()
		{
			return GL_INT_VEC3;
		}

		template<>
		inline static GLenum Vector<glm::ivec4>()
		{
			return GL_INT_VEC4;
		}

		// - UInt
		template<>
		inline static GLenum Vector<glm::uvec2>()
		{
			return GL_UNSIGNED_INT_VEC2;
		}

		template<>
		inline static GLenum Vector<glm::uvec3>()
		{
			return GL_UNSIGNED_INT_VEC3;
		}

		template<>
		inline static GLenum Vector<glm::uvec4>()
		{
			return GL_UNSIGNED_INT_VEC4;
		}

		// - Float
		template<>
		inline static GLenum Vector<glm::fvec2>()
		{
			return GL_FLOAT_VEC2;
		}

		template<>
		inline static GLenum Vector<glm::fvec3>()
		{
			return GL_FLOAT_VEC3;
		}

		template<>
		inline static GLenum Vector<glm::fvec4>()
		{
			return GL_FLOAT_VEC4;
		}

		// - Double
		template<>
		inline static GLenum Vector<glm::dvec2>()
		{
			return GL_DOUBLE_VEC2;
		}

		template<>
		inline static GLenum Vector<glm::dvec3>()
		{
			return GL_DOUBLE_VEC3;
		}

		template<>
		inline static GLenum Vector<glm::dvec4>()
		{
			return GL_DOUBLE_VEC4;
		}
	};

	// inline GLenum GetMatrix<T>()
	namespace
	{
		template<typename T>
		inline static GLenum Matrix()
		{
			static_assert(false, "Error: Invalid template argument.");
		}

		// - FLOAT
		// - 2 x N
		template<>
		inline static GLenum Matrix<glm::fmat2x2>()
		{
			return GL_FLOAT_MAT2;
		}

		template<>
		inline static GLenum Matrix<glm::fmat2x3>()
		{
			return GL_FLOAT_MAT2x3;
		}

		template<>
		inline static GLenum Matrix<glm::fmat2x4>()
		{
			return GL_FLOAT_MAT2x4;
		}

		// - 3 x N
		template<>
		inline static GLenum Matrix<glm::fmat3x2>()
		{
			return GL_FLOAT_MAT3x2;
		}

		template<>
		inline static GLenum Matrix<glm::fmat3x3>()
		{
			return GL_FLOAT_MAT3;
		}

		template<>
		inline static GLenum Matrix<glm::fmat3x4>()
		{
			return GL_FLOAT_MAT3x4;
		}

		// - 4 x N
		template<>
		inline static GLenum Matrix<glm::fmat4x2>()
		{
			return GL_FLOAT_MAT4x2;
		}

		template<>
		inline static GLenum Matrix<glm::fmat4x3>()
		{
			return GL_FLOAT_MAT4x3;
		}

		template<>
		inline static GLenum Matrix<glm::fmat4x4>()
		{
			return GL_FLOAT_MAT4;
		}

		// - DOUBLE
		// - 2 x N
		template<>
		inline static GLenum Matrix<glm::dmat2x2>()
		{
			return GL_DOUBLE_MAT2;
		}

		template<>
		inline static GLenum Matrix<glm::dmat2x3>()
		{
			return GL_DOUBLE_MAT2x3;
		}

		template<>
		inline static GLenum Matrix<glm::dmat2x4>()
		{
			return GL_DOUBLE_MAT2x4;
		}

		// - 3 x N
		template<>
		inline static GLenum Matrix<glm::dmat3x2>()
		{
			return GL_DOUBLE_MAT3x2;
		}

		template<>
		inline static GLenum Matrix<glm::dmat3x3>()
		{
			return GL_DOUBLE_MAT3;
		}

		template<>
		inline static GLenum Matrix<glm::dmat3x4>()
		{
			return GL_DOUBLE_MAT3x4;
		}

		// - 4 x N
		template<>
		inline static GLenum Matrix<glm::dmat4x2>()
		{
			return GL_DOUBLE_MAT4x2;
		}

		template<>
		inline static GLenum Matrix<glm::dmat4x3>()
		{
			return GL_DOUBLE_MAT4x3;
		}

		template<>
		inline static GLenum Matrix<glm::dmat4x4>()
		{
			return GL_DOUBLE_MAT4;
		}
	};
};

#endif // EXAMPLE

