#include <Game.hpp>
#include <PandoraRenderer.hpp>
#include <sstream>
#include <cstring>
#include <iostream>

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
			0 << "." << HG_REVISION << " [" << HG_CHANGESET << "]";

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
		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
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

