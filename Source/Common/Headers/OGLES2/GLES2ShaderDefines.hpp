#ifndef __DAWN_OGLES2_GLES2SHADERDEFINES_HPP__
#define __DAWN_OGLES2_GLES2SHADERDEFINES_HPP__

#include <Renderer.hpp>

namespace Dawn
{
	typedef enum __D_VERTEXTYPE
	{
		D_VERTEXTYPE_FLOAT	= 0,
		D_VERTEXTYPE_FLOAT2,
		D_VERTEXTYPE_FLOAT3,
		D_VERTEXTYPE_FLOAT4,

		D_VERTEXTYPE_INT,
		D_VERTEXTYPE_INT2,
		D_VERTEXTYPE_INT3,
		D_VERTEXTYPE_INT4,

		D_VERTEXTYPE_BOOL,
		D_VERTEXTYPE_BOOL2,
		D_VERTEXTYPE_BOOL3,
		D_VERTEXTYPE_BOOL4,

		D_VERTEXTYPE_MAT2X2,
		D_VERTEXTYPE_MAT3X3,
		D_VERTEXTYPE_MAT4X4,

		D_VERTEXTYPE_UNKNOWN	= D_ENUM_PAD
	}D_VERTEXTYPE;

	typedef enum __D_SHADERTYPE
	{
		D_SHADERTYPE_VERTEX	= 1,
		D_SHADERTYPE_FRAGMENT = 2,
		D_SHADERTYPE_UNKNOWN	=	D_ENUM_PAD
	}D_SHADERTYPE;

	typedef struct __D_VERTEXATTRIBUTE
	{
		D_VERTEXTYPE	Type;
		char			*pName;
	}D_VERTEXATTRIBUTE;

	typedef struct __D_SHADERCONSTANT
	{
		void			*pData;
		char			*pName;
		D_SHADERTYPE	Type;

	}D_SHADERCONSTANT;

	typedef struct __D_TEXTUREUNIT
	{
		char	*pName;
		GLuint	Unit;
	}D_TEXTUREUNIT;

	typedef struct __D_SHADER
	{
		D_VERTEXATTRIBUTE	*pVertexAttribute;
		D_SHADERCONSTANT	*pShaderConstant;
		D_TEXTUREUNIT		*pTextureUnit;
	}D_SHADER;
}

#endif

