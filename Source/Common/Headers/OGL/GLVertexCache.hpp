// NOTES:
// OpenGL vertex buffer objects [VBO] require OpenGL 1.5, therefore this
// will only be used for OpenGL versions equal to, or greater than, 1.5

#ifndef __DAWN_OGL_GLVERTEXCACHE_HPP__
#define __DAWN_OGL_GLVERTEXCACHE_HPP__

#include <VertexCache.hpp>
#include <Renderer.hpp>

namespace Dawn
{
	class GLVertexCache : public VertexCache
	{
		GLVertexCache( const D_MEMSIZE p_MaxVertexCount,
			const D_MEMSIZE p_MaxIndexCount,
			const D_MEMSIZE p_AttributeCount,
			const D_UINT64 p_VertexAttributes,
			const D_MEMSIZE p_CacheLines );

		virtual ~GLVertexCache( );

		virtual D_UINT32 Initialise( );

		virtual D_UINT32 Add( const D_MEMSIZE p_VertexCount,
			const D_BYTE *p_pVertices,
			const D_MEMSIZE p_IndexCount,
			const D_BYTE *m_pIndices,
			const D_UINT32 p_MaterialID );

		virtual void Clear( );

		virtual void FlushLine( const D_MEMSIZE p_Index );
		virtual D_MEMSIZE FlushFullestLine( );
		virtual void Flush( );

		virtual D_UINT64 VertexAttributes( ) const
			{ return m_VertexAttributes; }
		virtual D_MEMSIZE AttributeCount( ) const
			{ return m_AttributeCount; }
		virtual D_MEMSIZE VertexCapacity( ) const
			{ return m_MaxVertices; }
		virtual D_MEMSIZE IndexCapacity( ) const
			{ return m_MaxIndices; }
		virtual D_MEMSIZE LineCount( ) const
			{ return m_CacheLines; }

	private:
		// Do not allow for a default constructor
		GLVertexCache( );

		virtual D_MEMSIZE AttribToSize( const D_BYTE p_Atrribute ) const;

		// Per-cache vertex and index count as well as the material ID in use
		D_MEMSIZE	*m_pVertexCount;
		D_MEMSIZE	*m_pIndexCount;
		D_UINT32	*m_pMaterialID;

		D_MEMSIZE m_MaxVertices;
		D_MEMSIZE m_MaxIndices;
		D_MEMSIZE m_Stride;
		D_MEMSIZE m_CacheLines;

		D_MEMSIZE	m_AttributeCount;
		D_UINT64	m_VertexAttributes;

		// OpenGL-specific data
		GLuint	*m_pVertexBuffer;
		GLuint	*m_pIndexBuffer;
		GLuint	m_VertexAttributeID;
	};
}

#endif
