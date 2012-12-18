#include <OGL/GLExtender.hpp>

#ifdef BUILD_DEBUG
#include <iostream>
#endif

PFNGLBINDVERTEXARRAYPROC	__dglBindVertexArray = D_NULL;


namespace Dawn
{
	D_UINT32 GLExtender::Initialise( )
	{
		const GLubyte *pExtensions = dglGetString( GL_EXTENSIONS );
		const char *pExtensionsString = 
			reinterpret_cast< const char * >( pExtensions );
		D_MEMSIZE ExtensionsLength = strlen( pExtensionsString );

		char EChar = '\0';
		D_MEMSIZE Caret = 0;
		D_MEMSIZE ELen = 0;

		for( D_MEMSIZE i = 0; i < ExtensionsLength; ++i )
		{
			EChar = pExtensionsString[ i ];

			if( EChar == ' ' )
			{
				char *pExtStr = new char[ ELen + 1 ];
				memset( pExtStr, '\0', ELen+1 );
				strncpy( pExtStr, pExtensionsString+Caret, ELen );

				m_GLExtensions.push_back( pExtStr );

				delete [ ] pExtStr;
				pExtStr = D_NULL;

				Caret += ( ELen + 1 );
				ELen = 0;

				++i;
			}

			++ELen;
		}

#ifdef BUILD_DEBUG
		OutputDebugStringA( "---------------------\n" );
		char pStr[ 1024 ] = { '\0' };
		sprintf( pStr, "OpenGL Extensions %ld\n", m_GLExtensions.size( ) );
		OutputDebugStringA( pStr );
		OutputDebugStringA( "---------------------\n" );
#endif

		std::list< std::string >::const_iterator Itr =
			m_GLExtensions.begin( );

		for( ; Itr != m_GLExtensions.end( ); ++Itr )
		{
			char pStr[ 1024 ] = { '\0' };
			sprintf( pStr, "\t%s\n", ( *Itr ).c_str( ) );
			OutputDebugStringA( pStr );
		}

		return D_OK;
	}
}
