#include <OGL/GLVertexCache.hpp>

namespace Dawn
{
	GLVertexCache::GLVertexCache( const D_MEMSIZE p_MaxVertexCount,
		const D_MEMSIZE p_MaxIndexCount, const D_MEMSIZE p_AttributeCount,
		const D_UINT64 p_VertexAttributes, const D_MEMSIZE p_CacheLines )
	{
		// Clear the attributes
		m_VertexAttributeID = 0;

		m_MaxVertices = p_MaxVertexCount;
		m_MaxIndices = p_MaxIndexCount;
		m_AttributeCount = p_AttributeCount;
		m_VertexAttributes = p_VertexAttributes;
		m_CacheLines = p_CacheLines;

		m_pIndexCount = D_NULL;
		m_pVertexCount = D_NULL;
		m_pIndexBuffer = D_NULL;
		m_pVertexBuffer = D_NULL;
		m_pMaterialID = D_NULL;

		// Get the vertex stride based upon the vertex attributes passed in
		m_Stride = 0;

		for( D_MEMSIZE i = 0; i < m_AttributeCount; ++i )
		{
			// As an attribute is a four-bit value, extract a nybble from the
			// attributes pushed in
			D_BYTE Attrib = 0x0F & ( m_VertexAttributes >> ( i*4 ) );
			m_Stride += this->AttribToSize( Attrib );
		}
	}

	GLVertexCache::~GLVertexCache( )
	{
		// Flush all buffers and delete them
		this->Flush( );

		// UNCOMMENT!
		//glBindVertexArray( 0 );
		// !UNCOMMENT

		if( m_pVertexBuffer != D_NULL )
		{
			//glDelteBuffers( m_CacheLines, m_pVertexBuffer );
			delete [ ] m_pVertexBuffer;
			m_pVertexBuffer = D_NULL;
		}

		if( m_pIndexBuffer != D_NULL )
		{
			//glDelteBuffers( m_CacheLines, m_pIndexBuffer );
			delete [ ] m_pIndexBuffer;
			m_pIndexBuffer = D_NULL;
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

		if( m_pMaterialID != D_NULL  )
		{
			delete [ ] m_pMaterialID;
			m_pMaterialID = D_NULL;
		}
	}

	D_UINT32 GLVertexCache::Initialise( )
	{
		// Everything below assumes that values passed into the constructor
		// were greater than zero!
		m_pVertexBuffer = new GLuint[ m_CacheLines ];
		m_pIndexBuffer = new GLuint[ m_CacheLines ];
		m_pVertexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pIndexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pMaterialID = new D_UINT32[ m_CacheLines ];

		// Generate and bind the vertex array ID and vertex buffer
		//glGenVertexArrays( 1, &m_VertexAttributeID );

		//glBindVertexArray( m_VertexAttributeID );

		//glGenBuffers( m_CacheLines, m_pVertexBuffer );
		//glGenBuffers( m_CahceLines, m_pIndexBuffer );

		GLenum Error = 0;

		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			// Set the index and vertex counts to zero as well as the
			// material ID for each cache line
			m_pVertexCount[ i ] = 0;
			m_pIndexCount[ i ] = 0;
			m_pMaterialID[ i ] = 0;

			//glBindBuffer( GL_ARRAY_BUFFER, m_pVertexBuffer[ i ] );

			// Allocate memeory for a streaming buffer
			//glBufferData( GL_ARRAY_BUFFER, m_MaxVertices*m_Stride,
			//	D_NULL, GL_DYNAMIC_DRAW );

			//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pIndexBuffer[ i ] );
			//glBufferData( GL_ELEMENT_ARRAY_BUFFER,
			//	m_MaxIndices*sizeof( D_UINT16 ), D_NULL, GL_DYNAMIC_DRAW );

			// Was the buffer allocated without incident?
			Error = glGetError( );

			if( Error == GL_OUT_OF_MEMORY )
			{
				return D_ERROR_GRAPHICS;
			}
		}

		// Done with the array, be nice!
		//glBindVertexArray( 0 );

		return D_OK;
	}

	D_UINT32 GLVertexCache::Add( const D_MEMSIZE p_VertexCount,
		const D_BYTE *p_pVertices, const D_MEMSIZE p_IndexCount,
		const D_BYTE *p_pIndices, const D_UINT32 p_MaterialID )
	{
		return D_OK;
	}

	void GLVertexCache::Clear( )
	{
	}

	void GLVertexCache::FlushLine( const D_MEMSIZE p_Index )
	{
	}

	D_MEMSIZE GLVertexCache::FlushFullestLine( )
	{
		return 0;
	}

	void GLVertexCache::Flush( )
	{
	}

	D_MEMSIZE GLVertexCache::AttribToSize( const D_BYTE p_Attribute ) const
	{
		return 0;
	}
}
