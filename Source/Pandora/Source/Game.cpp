#include <Game.hpp>
#include <PandoraRenderer.hpp>
#include <sstream>
#include <cstring>
#include <iostream>
#include <OGLES2/GLES2VertexCache.hpp>
#include <OGLES2/GLES2Shader.hpp>
#include <Matrix4x4.hpp>
#include <GitVersion.hpp>

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

		Screen *pScreen = DefaultScreenOfDisplay( m_pDisplay );
		D_UINT32 X = 0, Y = 0, Width = 0, Height = 0;

		// Regardless of the fullscreen flag, if the width or height are
		// 800x480 or less, set it to the width and height of the screen
		// Basically, don't allow for a window at a resolution less than or
		// equal to 800x480
		Width = WidthOfScreen( pScreen );
		Height = HeightOfScreen( pScreen );

		if( Width <= 800 || Height <= 480 )
		{
			m_FullScreen = D_TRUE;
		}

		if( m_FullScreen )
		{
			Width = WidthOfScreen( pScreen );
			Height = HeightOfScreen( pScreen );
		}
		else
		{
			D_FLOAT32 FWidth = static_cast< D_FLOAT32 >( Width );
			D_FLOAT32 FHeight = static_cast< D_FLOAT32 >( Height );

			X = static_cast< D_UINT32 >( ( FWidth / 100.0f )*5.0f );
			Y = static_cast< D_UINT32 >( ( FHeight / 100.0f )*5.0f );

			Width = static_cast< D_UINT32 >( ( FWidth / 100.0f )*90.0f );
			Height = static_cast< D_UINT32 >( ( FHeight / 100.0f )*90.0f );
		}

		XSetWindowAttributes WinAttribs;
		WinAttribs.border_pixel = 0;
		WinAttribs.event_mask = StructureNotifyMask | ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask |
			FocusChangeMask | EnterWindowMask | LeaveWindowMask;
		WinAttribs.override_redirect = True;
		m_Window = XCreateWindow( m_pDisplay, DefaultRootWindow( m_pDisplay ),
			X, Y, Width, Height, 0,
			CopyFromParent, InputOutput, CopyFromParent,
			CWEventMask | CWBorderPixel | CWOverrideRedirect,
			&WinAttribs );
		
		// Hide the cursor
		Pixmap BlankPointer;
		XColor BlankColor;
		char Data[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		Cursor NoCursor;
		XColor Black, Dummy;
		Colormap NoColourmap;

		NoColourmap = DefaultColormap( m_pDisplay,
			DefaultScreen( m_pDisplay ) );
		XAllocNamedColor( m_pDisplay, NoColourmap, "black", &Black,
			&Dummy );
		BlankPointer = XCreateBitmapFromData( m_pDisplay, m_Window, Data,
			8, 8 );

		NoCursor = XCreatePixmapCursor( m_pDisplay, BlankPointer,
			BlankPointer, &Black, &Black, 0, 0 );

		XDefineCursor( m_pDisplay, m_Window, NoCursor );
		XFreeCursor( m_pDisplay, NoCursor );
		if( BlankPointer != None )
		{
			XFreePixmap( m_pDisplay, BlankPointer );
		}
		XFreeColors( m_pDisplay, NoColourmap, &Black.pixel, 1, 0 );

		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );

		XMoveWindow( m_pDisplay, m_Window, X, Y );

		// Set the window to fullscreen if applicable
		if( m_FullScreen )
		{
			XEvent Ev;
			Atom WM_State = XInternAtom( m_pDisplay, "_NET_WM_STATE", False );
			Atom WM_FullScreen = XInternAtom( m_pDisplay,
				"_NET_WM_STATE_FULLSCREEN", False );
			memset( &Ev, 0, sizeof( Ev ) );

			Ev.type = ClientMessage;
			Ev.xclient.window = m_Window;
			Ev.xclient.message_type = WM_State;
			Ev.xclient.format = 32;
			Ev.xclient.data.l[ 0 ] = 1;
			Ev.xclient.data.l[ 1 ] = WM_FullScreen;
			Ev.xclient.data.l[ 2 ] = 0;

			XSendEvent( m_pDisplay, DefaultRootWindow( m_pDisplay ), False,
				SubstructureNotifyMask, &Ev );
		}

		// Append the Mercurial version information to the window title
		std::stringstream CompleteTitle;

		CompleteTitle << g_pWindowTitle << " Ver. " << 0 << "." << 0 << "." <<
			0 << "." << GIT_ROLLINGCOUNT << " [" << GIT_COMMITHASH << " | "
			<< GIT_COMMITTERDATE << "]";

		m_pWindowTitle = new char[ CompleteTitle.str( ).size( ) + 1 ];
		strncpy( m_pWindowTitle, CompleteTitle.str( ).c_str( ),
			CompleteTitle.str( ).size( ) );
		m_pWindowTitle[ CompleteTitle.str( ).size( ) ] = '\0';

		XStoreName( m_pDisplay, m_Window, m_pWindowTitle );

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );
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
				case EnterNotify:
				{
					std::cout << "Got focus!\n";
					XGrabKeyboard( m_pDisplay, m_Window, True, GrabModeAsync,
						GrabModeAsync, CurrentTime );
					XGrabPointer( m_pDisplay, m_Window, True,
						EnterWindowMask | LeaveWindowMask | PointerMotionMask,
						GrabModeAsync, GrabModeAsync, None, None,
						CurrentTime );
					break;
				}
				case LeaveNotify:
				{
					std::cout << "Lost focus\n";
					XUngrabKeyboard( m_pDisplay, CurrentTime );
					XUngrabPointer( m_pDisplay, CurrentTime );
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
		static D_FLOAT32 YRot = 0.0f;

		D_FLOAT32 pVerts [ ] =
		{
			-0.4f, -0.4f, 0.0f,
			0.0f, 0.4f, 0.0f,
			0.4f, -0.4f, 0.0f
		};
		GLushort pInd[ ] = { 0, 1, 2 };

		m_pCache->Add( 3, ( D_BYTE * )pVerts, 3, pInd, 1 );
	
		const char *Vert = 
		"attribute vec3 vPos;\nuniform mat4 uWVP;\nvoid main( )\n{\ngl_Position = uWVP * vec4( vPos, 1.0 );\n}\n";
		const char *Frag =
		"precision mediump float;\nvoid main( )\n{\ngl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );\n}\n";

		Dawn::GLES2Shader Shader;
		Dawn::GLES2ShaderData Shad;
		Dawn::D_VERTEXATTRIBUTE Attr;
		Attr.Location = 0;
		Attr.pName = "vPos";

		D_FLOAT32 Matrix[ 16 ];

		Dawn::Matrix4x4 RotY;

		RotY.RotateY( YRot );
		YRot += 0.01f;

		RotY.GetMatrix( Matrix );

		Shader.Compile( Vert, D_SHADERTYPE_VERTEX );
		Shader.Compile( Frag, D_SHADERTYPE_FRAGMENT );
		Shad.AddVertexAttribute( Attr );
		Shader.Link( Shad );
		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		Shader.Activate( );

		// Doesn't care about shader type -- also, there's only one thing to
		// set
		Shader.SetConstantData( Matrix, D_SHADERTYPE_VERTEX );

		m_pCache->Flush( );
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

