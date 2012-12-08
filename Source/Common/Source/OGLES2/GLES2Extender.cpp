#include <OGLES2/GLES2Extender.hpp>
#include <iostream>
#include <cstring>

PFNGLGENVERTEXARRAYSOESPROC		__dglGenVertexArrays = D_NULL;
PFNGLBINDVERTEXARRAYOESPROC 	__dglBindVertexArray = D_NULL;
PFNGLISVERTEXARRAYOESPROC		__dglIsVertexArray = D_NULL;
PFNGLDELETEVERTEXARRAYSOESPROC	__dglDeleteVertexArrays;

namespace Dawn
{
	D_UINT32 GLES2Extender::Initialise( )
	{
		// Query and store the OGLES2 extensions
		const GLubyte *pExtensions = dglGetString( GL_EXTENSIONS );
		const char *pExtensionsStr =
			reinterpret_cast< const char * >( pExtensions );
		D_MEMSIZE ExtensionsLen = strlen( pExtensionsStr );

		char EChar = '\0';
		D_MEMSIZE Caret = 0;
		D_MEMSIZE ELen = 0;

		for( D_MEMSIZE i = 0; i < ExtensionsLen; ++i )
		{
			EChar = pExtensionsStr[ i ];

			// Space is the delimiter
			if( EChar == ' ' )
			{
				char *pExtStr = new char[ ELen + 1 ];
				memset( pExtStr, '\0', ELen+1 );
				strncpy( pExtStr, pExtensionsStr+Caret, ELen );

				m_GLES2Extensions.push_back( pExtStr );

				delete [ ] pExtStr;
				pExtStr = D_NULL;

				Caret += ELen+1;
				ELen = 0;

				++i;
			}
			++ELen;
		}

		std::cout << "-------------------------------" << std::endl;
		std::cout << "OpenGL | ES 2.0 Extensions: " <<
			m_GLES2Extensions.size( ) << std::endl;
		std::cout << "-------------------------------" << std::endl;

		std::list< std::string >::iterator Itr = m_GLES2Extensions.begin( );
		for( ; Itr != m_GLES2Extensions.end( ); ++Itr )
		{
			std::cout << "\t" << ( *Itr ).c_str( ) << std::endl;
		}

		D_BOOL Ret = D_FALSE;

		Itr = m_GLES2Extensions.begin( );
		for( ; Itr != m_GLES2Extensions.end( ); ++Itr )
		{
			if( ( *Itr ).compare( "GL_OES_vertex_array_object" ) == 0 )
			{
				Ret = ( ( __dglGenVertexArrays =
					( PFNGLGENVERTEXARRAYSOESPROC )eglGetProcAddress(
						"glGenVertexArraysOES" ) ) == D_NULL ) || Ret;
				Ret = ( ( __dglBindVertexArray =
					( PFNGLBINDVERTEXARRAYOESPROC )eglGetProcAddress(
						"glBindVertexArrayOES" ) ) == D_NULL ) || Ret;
				Ret = ( ( __dglIsVertexArray =
					( PFNGLISVERTEXARRAYOESPROC )eglGetProcAddress(
						"glIsVertexArrayOES" ) ) == D_NULL ) || Ret;
				Ret = ( ( __dglDeleteVertexArrays =
					( PFNGLDELETEVERTEXARRAYSOESPROC )eglGetProcAddress(
						"glDeleteVertexArraysOES" ) ) == D_NULL ) || Ret;
#ifdef BUILD_DEBUG
				if( __dglGenVertexArrays && __dglBindVertexArray &&
					__dglIsVertexArray && __dglDeleteVertexArrays )
				{
					std::cout << "[Dawn::GLES2Extender::Initialise] " <<
						"<INFO> Successfully bound " <<
						"GL_OES_vertex_array_object functions" << std::endl;
				}
				else
				{
					std::cout << "[Dawn::GLES2Extender::Initialise] " <<
						"<ERROR> Failed to bind GL_OES_vertex_array_object " <<
						"functions" << std::endl;
				}
#endif
			}
		}
		
		return ( Ret ? D_FAIL : D_OK );
	}
}

