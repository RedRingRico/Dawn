#ifndef __DAWN_GLES2VERTEXCACHE_HPP__
#define __DAWN_GLES2VERTEXCACHE_HPP__

#include <VertexCache.hpp>
#include <Renderer.hpp>

namespace Dawn
{
	class GLES2VertexCache : public VertexCache
	{
	public:
		GLES2VertexCache( const D_MEMSIZE p_MaxVertexCount,
			const D_MEMSIZE p_MaxIndexCount,
			const D_MEMSIZE p_AttributeCount,
			const D_UINT64 p_VertexAttributes,
			const D_MEMSIZE p_CacheLines );
		virtual ~GLES2VertexCache( );

		virtual D_UINT32 Initialise( );

		virtual D_UINT32 Add( const D_MEMSIZE p_VertexCount,
			const D_BYTE *p_pVertices,
			const D_MEMSIZE p_IndexCount,
			const D_BYTE *p_pIndices,
			const D_UINT32 p_MaterialID );

		virtual void Clear( );

		virtual void FlushLine( const D_MEMSIZE p_Index );

		virtual D_MEMSIZE FlushFullestLine( );

		virtual void Flush( );

		virtual D_UINT64 Attributes( ) const;
		virtual D_MEMSIZE AttributeCount( ) const;
		virtual D_MEMSIZE VertexCapacity( ) const;
		virtual D_MEMSIZE IndexCapacity( ) const;
		virtual D_MEMSIZE LineCount( ) const;

	private:
		// Do not allow for a default constructor.  Use the parameter-based
		// constructor, instead
		GLES2VertexCache( );

		virtual D_MEMSIZE AttribToSize( D_BYTE p_Attribute ) const;

		D_MEMSIZE	*m_pVertexCount;
		D_MEMSIZE	*m_pIndexCount;
		D_UINT32	*m_pMaterialID;
		
		D_MEMSIZE m_MaxVertexCount;
		D_MEMSIZE m_MaxIndexCount;
		D_MEMSIZE m_Stride;
		D_MEMSIZE m_CacheLines;

		D_MEMSIZE	m_AttributeCount;
		// Should attributes be a pointer of D_BYTES?
		D_UINT64	m_VertexAttributes;

		GLuint	*m_pVertexBuffer;
		GLuint	*m_pIndexBuffer;
		GLuint	m_VertexAttributeID;
	};
}

#endif

