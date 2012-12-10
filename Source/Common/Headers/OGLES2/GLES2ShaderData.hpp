#ifndef __DAWN_OGLES2_GLES2SHADERDATA_HPP__
#define __DAWN_OGLES2_GLES2SHADERDATA_HPP__

#include <ShaderData.hpp>
#include <list>

namespace Dawn
{
	class GLES2ShaderData : public ShaderData
	{
	public:
		GLES2ShaderData( ){ }
		virtual ~GLES2ShaderData( ){ }

		virtual void AddVertexAttribute(
			const D_VERTEXATTRIBUTE &p_VertexAttribute );
		virtual void AddShaderConstant(
			const D_SHADERCONSTANT &p_ShaderConstant );
		virtual void AddTextureUnit( const D_TEXTUREUNIT &p_TexureUnit );

		virtual D_MEMSIZE VertexAttributeCount( ) const;

		virtual D_VERTEXATTRIBUTE GetVertexAttribute(
			const D_MEMSIZE p_Index ) const;

	private:
		std::list< D_VERTEXATTRIBUTE >	m_VertexAttribute;
		std::list< D_SHADERCONSTANT >	m_ShaderConstant;
		std::list< D_TEXTUREUNIT >		m_TextureUnit;
	};
}

#endif

