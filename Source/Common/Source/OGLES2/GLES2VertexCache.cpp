#include <OGLES2/GLES2VertexCache.hpp>

namespace Dawn
{
	GLES2VertexCache::GLES2VertexCache( const D_MEMSIZE p_MaxVertexCount,
		const D_MEMSIZE p_MaxIndexCount, const D_MEMSIZE p_AttributeCount,
		const D_UINT64 p_VertexAttributes, const D_MEMSIZE p_CacheLines )
	{
		m_MaxVertexCount = p_MaxVertexCount;
		m_MaxIndexCount = p_MaxIndexCount;
		m_AttributeCount = p_AttributeCount;
		m_VertexAttributes = p_VertexAttributes;

		m_pVertexCount = D_NULL;
		m_pIndexCount = D_NULL;
		m_pVertexBuffer = D_NULL;
		m_pIndexBuffer = D_NULL;
		m_pMaterialID = D_NULL;
		m_VertexAttributeID = D_NULL;

		// Get the vertex stride based upon the vertex attributes passed in
		m_Stride = 0;

		for( D_MEMSIZE i = 0; i < m_AttributeCount; ++i )
		{
			// Extract each nybble from the attributes
			D_BYTE Attrib = 0x0F & ( m_VertexAttributes >> ( i*4 ) );
			m_Stride = this->AttribToSize( Attrib );
		}

	}

	GLES2VertexCache::~GLES2VertexCache( )
	{
		this->Flush( );

		dglBindVertexArray( 0 );

		if( m_pVertexBuffer != D_NULL )
		{
			glDeleteBuffers( m_CacheLines, m_pVertexBuffer );
			delete [ ] m_pVertexBuffer;
			m_pVertexBuffer = D_NULL;
		}

		if( m_pIndexBuffer != D_NULL )
		{
			glDeleteBuffers( m_CacheLines, m_pIndexBuffer );
			delete [ ] m_pIndexBuffer;
			m_pIndexBuffer = D_NULL;
		}

		if( m_pMaterialID != D_NULL )
		{
			delete [ ] m_pMaterialID;
			m_pMaterialID = D_NULL;
		}

		if( m_pVertexCount != D_NULL )
		{
			delete [ ] m_pVertexCount;
			m_pVertexCount = D_NULL;
		}

		if( m_pIndexCount != D_NULL )
		{
			delete [ ] m_pIndexCount;
			m_pIndexCount = D_NULL;
		}
	}

	D_UINT32 GLES2VertexCache::Initialise( )
	{
		m_pVertexBuffer = new GLuint[ m_CacheLines ];
		m_pIndexBuffer = new GLuint[ m_CacheLines ];
		m_pVertexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pIndexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pMaterialID = new D_UINT32[ m_CacheLines ];

		// Generate the vertex array ID
		//glGenVertexArrays( 1, &m_VertexAttributeID );
		
		dglBindVertexArray( m_VertexAttributeID );

		glGenBuffers( m_CacheLines, m_pVertexBuffer );
		glGenBuffers( m_CacheLines, m_pIndexBuffer );

		GLenum Error = 0;

		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			// Set the index and vertex counts to zero as well as the
			// material ID for each cache line
			m_pVertexCount[ i ] = 0;
			m_pIndexCount[ i ] = 0;
			m_pMaterialID[ i ] = 0;

			glBindBuffer( GL_ARRAY_BUFFER, m_pVertexBuffer[ i ] );

			// Allocate memory for a streaming buffer
			glBufferData( GL_ARRAY_BUFFER, m_MaxVertexCount*m_Stride,
				D_NULL, GL_DYNAMIC_DRAW );

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pIndexBuffer[ i ] );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER,
				m_MaxIndexCount*sizeof( D_UINT16 ),
				D_NULL, GL_DYNAMIC_DRAW );

			Error = glGetError( );

			if( Error == GL_OUT_OF_MEMORY )
			{
				return D_ERROR_GRAPHICS;
			}
		}

		// Done with the array
		dglBindVertexArray( 0 );

		return D_OK;
	}
	
	D_UINT32 GLES2VertexCache::Add( const D_MEMSIZE p_VertexCount,
		const D_BYTE *p_pVertices, const D_MEMSIZE p_IndexCount,
		const D_BYTE *p_pIndices, const D_UINT32 p_MaterialID )
	{
		return D_OK;
	}

	void GLES2VertexCache::Clear( )
	{
	}

	void GLES2VertexCache::FlushLine( const D_MEMSIZE p_Index )
	{
	}

	D_MEMSIZE GLES2VertexCache::FlushFullestLine( )
	{
		return 0;
	}

	void GLES2VertexCache::Flush( )
	{
	}

	D_UINT64 GLES2VertexCache::Attributes( ) const
	{
		return 0;
	}

	D_MEMSIZE GLES2VertexCache::AttributeCount( ) const
	{
		return 0;
	}

	D_MEMSIZE GLES2VertexCache::VertexCapacity( ) const
	{
		return 0;
	}

	D_MEMSIZE GLES2VertexCache::IndexCapacity( ) const
	{
		return 0;
	}

	D_MEMSIZE GLES2VertexCache::LineCount( ) const
	{
		return 0;
	}

	D_MEMSIZE GLES2VertexCache::AttribToSize( D_BYTE p_Attribute ) const
	{
		return 0;
	}
}

