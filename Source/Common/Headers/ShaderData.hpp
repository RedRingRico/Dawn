#ifndef __DAWN_SHADERDATA_HPP__
#define __DAWN_SHADERDATA_HPP__

#include <Renderer.hpp>

#if ( PLATFORM_PANDORA )
#include <OGLES2/GLES2ShaderDataTypes.hpp>
#endif

namespace Dawn
{
	class ShaderData
	{
	public:
		virtual ~ShaderData( ){ }

		virtual void AddVertexAttribute(
			const D_VERTEXATTRIBUTE &p_VertexAttribute ) = 0;
		virtual void AddShaderConstant(
			const D_SHADERCONSTANT &p_ShaderConstant ) = 0;
		virtual void AddTextureUnit( const D_TEXTUREUNIT &p_TexureUnit ) = 0;

		virtual D_MEMSIZE VertexAttributeCount( ) const = 0;

		virtual D_VERTEXATTRIBUTE GetVertexAttribute(
			const D_MEMSIZE p_Index ) const = 0;
	};	
}

#endif

