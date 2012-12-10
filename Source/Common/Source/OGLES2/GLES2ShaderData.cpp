#include <OGLES2/GLES2ShaderData.hpp>

namespace Dawn
{
	void GLES2ShaderData::AddVertexAttribute(
		const D_VERTEXATTRIBUTE &p_VertexAttribute )
	{
		m_VertexAttribute.push_back( p_VertexAttribute );
	}

	void GLES2ShaderData::AddShaderConstant(
		const D_SHADERCONSTANT &p_ShaderConstant )
	{
		m_ShaderConstant.push_back( p_ShaderConstant );
	}

	void GLES2ShaderData::AddTextureUnit( const D_TEXTUREUNIT &p_TextureUnit )
	{
		m_TextureUnit.push_back( p_TextureUnit );
	}

	D_MEMSIZE GLES2ShaderData::VertexAttributeCount( ) const
	{
		return m_VertexAttribute.size( );
	}

	D_VERTEXATTRIBUTE GLES2ShaderData::GetVertexAttribute(
		const D_MEMSIZE p_Index ) const
	{
		std::list< D_VERTEXATTRIBUTE >::const_iterator Itr =
			m_VertexAttribute.begin( );

		for( D_MEMSIZE i = 0; i < p_Index; ++i )
		{
			Itr++;
		}

		return ( *Itr );
	}
}

