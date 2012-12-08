#include <OGLES2/GLES2VertexCache.hpp>
#ifdef BUILD_DEBUG
#include <iostream>
#endif

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
		m_CacheLines = p_CacheLines;

		m_pVertexCount = D_NULL;
		m_pIndexCount = D_NULL;
		m_pVertexBuffer = D_NULL;
		m_pIndexBuffer = D_NULL;
		m_pMaterialID = D_NULL;
		m_pVertexArrayID = D_NULL;

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
			dglDeleteBuffers( m_CacheLines, m_pVertexBuffer );
			delete [ ] m_pVertexBuffer;
			m_pVertexBuffer = D_NULL;
		}

		if( m_pIndexBuffer != D_NULL )
		{
			dglDeleteBuffers( m_CacheLines, m_pIndexBuffer );
			delete [ ] m_pIndexBuffer;
			m_pIndexBuffer = D_NULL;
		}

		if( m_pVertexArrayID != D_NULL )
		{
			dglDeleteVertexArrays( m_CacheLines, m_pVertexArrayID );
			delete [ ] m_pVertexArrayID;
			m_pVertexArrayID = D_NULL;
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
		m_pVertexArrayID = new GLuint[ m_CacheLines ];
		m_pVertexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pIndexCount = new D_MEMSIZE[ m_CacheLines ];
		m_pMaterialID = new D_UINT32[ m_CacheLines ];

		// Generate all of the things
		dglGenVertexArrays( m_CacheLines, m_pVertexArrayID );
		
//		dglBindVertexArray( m_VertexAttributeID );

		dglGenBuffers( m_CacheLines, m_pVertexBuffer );
		dglGenBuffers( m_CacheLines, m_pIndexBuffer );

		GLenum Error = 0;

		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			// Set the index and vertex counts to zero as well as the
			// material ID for each cache line
			m_pVertexCount[ i ] = 0;
			m_pIndexCount[ i ] = 0;
			m_pMaterialID[ i ] = 0;

			dglBindVertexArray( m_pVertexArrayID[ i ] );

			dglBindBuffer( GL_ARRAY_BUFFER, m_pVertexBuffer[ i ] );

			// Allocate memory for a streaming buffer
			dglBufferData( GL_ARRAY_BUFFER, m_MaxVertexCount*m_Stride,
				D_NULL, GL_DYNAMIC_DRAW );

			dglBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pIndexBuffer[ i ] );
			dglBufferData( GL_ELEMENT_ARRAY_BUFFER,
				m_MaxIndexCount*sizeof( D_UINT16 ),
				D_NULL, GL_DYNAMIC_DRAW );

			Error = dglGetError( );

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
		const D_UINT16 *p_pIndices, const D_UINT32 p_MaterialID )
	{
		// Find a cache line with the same material ID
		// If there isn't a cache line available, render the fullest cache line
		// and use a new line
		D_UINT32 Material = 0;
		D_MEMSIZE CacheLine = 0;
		D_BOOL MaterialMatch = D_FALSE;

		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			if( m_pMaterialID[ i ] == p_MaterialID )
			{
				MaterialMatch = D_TRUE;
				Material = p_MaterialID;
				CacheLine = i;
				break;
			}
		}

		if( MaterialMatch != D_TRUE )
		{
			CacheLine = FlushFullestLine( );
		}

		if( p_VertexCount > m_MaxVertexCount )
		{
#ifdef BUILD_DEBUG
			std::cout << "[Dawn::GLES2VertexCache::Add] <ERROR> " <<
				"Failed to allocate vertices" << std::endl;
			std::cout << "\tAttempted to allocate " << p_VertexCount << 
				" vertices.  Capacity: " << m_MaxVertexCount << std::endl;
#endif
			return D_ERROR;
		}
		
		if( p_IndexCount > m_MaxIndexCount )
		{
#ifdef BUILD_DEBUG
			std::cout << "[Dawn::GLES2VertexCache::Add] <ERROR> " <<
				"Failed to allocate indices" << std::endl;
			std::cout << "\tAttempted to allocate " << p_IndexCount <<
				" indices.  Capacity: " << m_MaxIndexCount << std::endl;
#endif
			return D_ERROR;
		}
		
		if( p_VertexCount >
			( m_MaxVertexCount - m_pVertexCount[ CacheLine ] ) )
		{
			this->FlushLine( CacheLine );
		}
		if( p_IndexCount > ( m_MaxIndexCount - m_pIndexCount[ CacheLine ] ) )
		{
			this->FlushLine( CacheLine );
		}

		// Add the vertices!
		dglBindVertexArray( m_pVertexArrayID[ CacheLine ] );

		dglBindBuffer( GL_ARRAY_BUFFER, m_pVertexBuffer[ CacheLine ] );
		dglBufferSubData( GL_ARRAY_BUFFER,
			m_pVertexCount[ CacheLine ]*m_Stride,
			p_VertexCount*m_Stride, p_pVertices );

		D_MEMSIZE AccDimension = 0;
		for( D_MEMSIZE i = 0; i < m_AttributeCount; ++i )
		{
			D_MEMSIZE Dimension = 0;
			GLenum Type = GL_INVALID_ENUM;
			D_MEMSIZE TypeSize = 0;
			D_BYTE Attrib = 0x0F & ( m_VertexAttributes >> ( i*4 ) );

			Dimension = 0x03 & ( Attrib ) + 1;

			switch( ( 0x0C & ( Attrib ) ) >> 2 )
			{
				case 0:
				{
					Type = GL_INT;
					TypeSize = sizeof( D_INT32 );
					break;
				}
				case 1:
				{
					Type = GL_FLOAT;
					TypeSize = sizeof( D_FLOAT32 );
					break;
				}
				case 2:
				{
					//Type = GL_DOUBLE;
					TypeSize = sizeof( D_FLOAT64 );
					break;
				}
				case 3:
				{
					Type = GL_FLOAT;
					TypeSize = sizeof( D_FLOAT32 );
					Dimension *= Dimension;
					break;
				}
			}

			dglVertexAttribPointer( i, Dimension, Type, GL_FALSE,
				m_Stride, D_BUFFER_OFFSET( TypeSize*AccDimension ) );
			dglEnableVertexAttribArray( i );

			AccDimension += Dimension;
		}

		GLenum Error = dglGetError( );

		if( Error == GL_OUT_OF_MEMORY )
		{
			dglBindBuffer( GL_ARRAY_BUFFER, 0 );
			dglBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
#ifdef BUILD_DEBUG
			std::cout << "[Dawn::GLES2VertexCache::Add] <ERROR> " <<
				"Not enough memory on the GLES server" << std::endl;
#endif
			return D_ERROR_GRAPHICS;
		}

		D_UINT16 *pIndices = new D_UINT16[ p_IndexCount ];
		for( D_MEMSIZE i = 0; i < p_IndexCount; ++i )
		{
			pIndices[ i ] = p_pIndices[ i ] + m_pVertexCount[ CacheLine ];
		}

		dglBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pIndexBuffer[ CacheLine ] );
		dglBufferSubData( GL_ELEMENT_ARRAY_BUFFER,
			m_pIndexCount[ CacheLine ]*sizeof( D_UINT16 ),
			p_IndexCount*sizeof( D_UINT16 ), pIndices );

		delete [ ] pIndices;

		Error = dglGetError( );

		if( Error == GL_OUT_OF_MEMORY )
		{
			dglBindBuffer( GL_ARRAY_BUFFER, 0 );
			dglBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
#ifdef BUILD_DEBUG
			std::cout << "[Dawn::GLES2VertexCache::Add] <ERROR> " <<
				"Not enough memory on the GLES server" << std::endl;
#endif
			return D_ERROR_GRAPHICS;
		}

		// Everything went fine, increment the vertex and index counters
		m_pVertexCount[ CacheLine ] += p_VertexCount;
		m_pIndexCount[ CacheLine ] += p_IndexCount;

		// Unbind the buffer [be nice!]
		dglBindVertexArray( 0 );

		return D_OK;
	}

	void GLES2VertexCache::Clear( )
	{
		dglDeleteBuffers( m_CacheLines, m_pVertexBuffer );
		dglDeleteBuffers( m_CacheLines, m_pIndexBuffer );
	}

	void GLES2VertexCache::FlushLine( const D_MEMSIZE p_Index )
	{
		if( ( m_pVertexCount == D_NULL ) ||
			( m_pIndexCount == D_NULL ) )
		{
			return;
		}
		
		if( ( m_pVertexCount[ p_Index ] == 0 ) ||
			( m_pIndexCount[ p_Index ] == 0 ) )
		{
			return;
		}

		dglBindVertexArray( m_pVertexArrayID[ p_Index ] );
		dglDrawElements( GL_TRIANGLES, m_pIndexCount[ p_Index ],
			GL_UNSIGNED_SHORT, D_BUFFER_OFFSET( 0 ) );
		dglBindVertexArray( 0 );

		m_pVertexCount[ p_Index ] = 0;
		m_pIndexCount[ p_Index ] = 0;
	}

	D_MEMSIZE GLES2VertexCache::FlushFullestLine( )
	{
		D_MEMSIZE VertexCount = 0;
		D_MEMSIZE FullestLine = 0;

		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			if( m_pVertexCount[ i ] > VertexCount )
			{
				VertexCount = m_pVertexCount[ i ];
				FullestLine = i;
			}
		}

		this->FlushLine( FullestLine );

		return FullestLine;
	}

	void GLES2VertexCache::Flush( )
	{
		for( D_MEMSIZE i = 0; i < m_CacheLines; ++i )
		{
			this->FlushLine( i );
		}
	}

	D_UINT64 GLES2VertexCache::Attributes( ) const
	{
		return m_VertexAttributes;
	}

	D_MEMSIZE GLES2VertexCache::AttributeCount( ) const
	{
		return m_AttributeCount;
	}

	D_MEMSIZE GLES2VertexCache::VertexCapacity( ) const
	{
		return m_MaxVertexCount;
	}

	D_MEMSIZE GLES2VertexCache::IndexCapacity( ) const
	{
		return m_MaxIndexCount;
	}

	D_MEMSIZE GLES2VertexCache::LineCount( ) const
	{
		return m_CacheLines;
	}

	D_MEMSIZE GLES2VertexCache::AttribToSize( D_BYTE p_Attribute ) const
	{
		// Should be TTSS, where TT is type and SS is size
		// Get the first two bytes and multiply by the last two bytes
		D_BYTE Type = p_Attribute >> 2;
		// Mask the size bits
		// 0000 0011
		D_MEMSIZE Size = ( 0x03 & p_Attribute )+1;

		switch( Type )
		{
			// Int type
			case 0:
			{
				Size *= sizeof( D_INT32 );
				break;
			}
			// Single float type
			case 1:
			{
				Size *= sizeof( D_FLOAT32 );
				break;
			}
			// Double float type
			case 2:
			{
				Size *= sizeof( D_FLOAT64 );
				break;
			}
			// Matrix type
			case 3:
			{
				// n*n matrices
				Size *= Size;
				Size *= sizeof( D_FLOAT32 );
				break;
			}
		}

		return Size;
	}
}

