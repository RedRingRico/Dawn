#include <Game.hpp>
#include <PandoraRenderer.hpp>
#include <sstream>
#include <cstring>
#include <iostream>
#include <OGLES2/GLES2VertexCache.hpp>

namespace Dawn
{
	Game::Game( )
	{
		m_pRenderer = D_NULL;
		m_pConfigFile = D_NULL;
		m_pWindowTitle = D_NULL;
		m_FullScreen = D_FALSE;
	}

	Game::~Game( )
	{
		if( m_pWindowTitle )
		{
			delete [ ] m_pWindowTitle;
			m_pWindowTitle = D_NULL;
		}
		if( m_pRenderer )
		{
			delete m_pRenderer;
			m_pRenderer = D_NULL;
		}

		XDestroyWindow( m_pDisplay, m_Window );
		XCloseDisplay( m_pDisplay );
	}

	D_UINT32 Game::Initialise( const D_BOOL p_FullScreen )
	{
		m_FullScreen = p_FullScreen;

		m_pRenderer = new Dawn::PandoraRenderer( );
		m_pDisplay = XOpenDisplay( D_NULL );

		if( !m_pDisplay )
		{
			return D_ERROR;
		}

		XSetWindowAttributes WinAttribs;
		WinAttribs.border_pixel = 0;
		WinAttribs.event_mask = StructureNotifyMask | ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask;
		m_Window = XCreateWindow( m_pDisplay, DefaultRootWindow( m_pDisplay ),
			0, 0, 800, 480, 0,
			CopyFromParent, InputOutput, CopyFromParent,
			CWEventMask | CWBorderPixel,
			&WinAttribs );
			
		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );

		// Append the Mercurial version information to the window title
		std::stringstream CompleteTitle;

		CompleteTitle << g_pWindowTitle << " Ver. " << 0 << "." << 0 << "." <<
			0 << "." << HG_REVISION << ( HG_LOCAL_MODIFICATIONS ? "M" : "" ) <<
			" [" << HG_CHANGESET << "]";

		m_pWindowTitle = new char[ CompleteTitle.str( ).size( ) + 1 ];
		strncpy( m_pWindowTitle, CompleteTitle.str( ).c_str( ),
			CompleteTitle.str( ).size( ) );
		m_pWindowTitle[ CompleteTitle.str( ).size( ) ] = '\0';

		XStoreName( m_pDisplay, m_Window, m_pWindowTitle );

		m_Canvas.Width( 800 );
		m_Canvas.Height( 480 );
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.Colour( FORMAT_ARGB8 );
		m_Canvas.DepthStencil( FORMAT_D24S8 );

		m_pRenderer->SetDisplay( m_pDisplay );
		m_pRenderer->SetWindow( m_Window );
		m_pRenderer->Create( m_Canvas );
		m_pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

		Dawn::StartTime( );
		
		m_pCache = new Dawn::GLES2VertexCache( 1024, 1024, 1, 0x6, 10 );

		if( m_pCache->Initialise( ) != D_OK )
		{
			return D_ERROR;
		}

		return D_OK;
	}

	void Game::Update( const D_FLOAT64 p_ElapsedGameTime )
	{
		XEvent Events;
		KeySym Key;

		while( XPending( m_pDisplay ) > 0 )
		{
			XNextEvent( m_pDisplay, &Events );

			switch( Events.type )
			{
				case KeyPress:
				{
					Key = XLookupKeysym( &Events.xkey, 0 );
					if( Key == 'q' )
					{
						m_Running = D_FALSE;
					}
					break;
				}
				case ConfigureNotify:
				{
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	void Game::Render( )
	{
		D_FLOAT32 pVerts [ ] =
		{
			-0.4f, -0.4f, 0.0f,
			0.0f, 0.4f, 0.0f,
			0.4f, -0.4f, 0.0f
		};
		GLushort pInd[ ] = { 0, 1, 2 };

		m_pCache->Add( 3, ( D_BYTE * )pVerts, 3, pInd, 1 );

		GLint compile;
		const char *Vert = 
		"attribute vec3 vPos;\nvoid main( )\n{\ngl_Position = vec4( vPos, 1.0 );\n}\n";
		const char *Frag =
		"precision mediump float;\nvoid main( )\n{\ngl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );\n}\n";

		GLint Vshad, Fshad;
		Vshad = glCreateShader( GL_VERTEX_SHADER );
		Fshad = glCreateShader( GL_FRAGMENT_SHADER );

		glShaderSource( Vshad, 1, &Vert, NULL );
		glShaderSource( Fshad, 1, &Frag, NULL );

		glCompileShader( Vshad );
		glGetShaderiv( Vshad, GL_COMPILE_STATUS, &compile );
		if( !compile )
		{
			GLint infoLen = 0;
			glGetShaderiv( Vshad, GL_INFO_LOG_LENGTH, &infoLen );
			if( infoLen > 1 )
			{
				char *pLog = new char[ infoLen ];
				glGetShaderInfoLog( Vshad, infoLen, NULL, pLog );

				std::cout << pLog << std::endl;

				delete [ ] pLog;
			}
		}

		glCompileShader( Fshad );
		glGetShaderiv( Fshad, GL_COMPILE_STATUS, &compile );
		if( !compile )
		{
			GLint infoLen = 0;
			glGetShaderiv( Vshad, GL_INFO_LOG_LENGTH, &infoLen );
			if( infoLen > 1 )
			{
				char *pLog = new char[ infoLen ];
				glGetShaderInfoLog( Vshad, infoLen, NULL, pLog );

				std::cout << pLog << std::endl;

				delete [ ] pLog;
			}
		}

		GLint Prog = glCreateProgram( );
		if( Prog == 0 )
		{
		}

		glAttachShader( Prog, Vshad );
		glAttachShader( Prog, Fshad );

		glBindAttribLocation( Prog, 0, "vPos" );

		glLinkProgram( Prog );

		glGetProgramiv( Prog, GL_LINK_STATUS, &compile );
		if( !compile )
		{
			GLsizei infoLen = 0;
			glGetProgramiv( Prog, GL_INFO_LOG_LENGTH, &infoLen );
			if( infoLen > 1 )
			{
				char *pLog = new char[ infoLen];
				glGetProgramInfoLog( Prog, infoLen, NULL, pLog );
				std::cout << pLog;
				delete [ ] pLog;
			}
		}

		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		glUseProgram( Prog );
		m_pCache->Flush( );
//		m_pRenderer->EndScene( );
		glDeleteShader( Vshad );
		glDeleteShader( Fshad );
		glDeleteProgram( Prog );

		m_pRenderer->EndScene( );
	}

	D_UINT32 Game::Execute( )
	{
		m_Running = D_TRUE;

		while( m_Running == D_TRUE )
		{
			this->Update( 0.0f );
			this->Render( );
		}

		return D_OK;
	}
}

