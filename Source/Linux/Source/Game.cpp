#include <Game.hpp>
#include <LinuxRendererOGL1.hpp>

namespace Dawn
{
	Game::Game( )
	{
		m_pRenderer = D_NULL;
		m_pConfigFile = D_NULL;
		m_FullScreen = D_FALSE;
	}

	Game::~Game( )
	{
		if( m_pRenderer )
		{
			delete m_pRenderer;
		}

		XDestroyWindow( m_pDisplay, m_Window );
		XCloseDisplay( m_pDisplay );
	}

	D_UINT32 Game::Initialise( const D_BOOL p_FullScreen )
	{
		m_FullScreen = p_FullScreen;
		// TODO
		// Attempt to create an OpenGL 3 renderer, then fall back to 2,
		// finally try to get an OpenGL 1 renderer
		m_pRenderer = new Dawn::LinuxRendererOGL1( );

		XVisualInfo *pVI;
		Colormap ColourMap;
		XSetWindowAttributes WinAttrs;
		D_UINT32 X = 0, Y = 0, Width = 0, Height = 0;
		Screen *pScreen = D_NULL;

		m_pDisplay = XOpenDisplay( 0 );
		pScreen = DefaultScreenOfDisplay( m_pDisplay );

		// TODO
		// Load the Width and Height from file, centring the window if it is
		// to be windowed (as also defined in the configuraiton file)
		
		if( m_FullScreen == D_TRUE )
		{
			Width = WidthOfScreen( pScreen );
			Height = HeightOfScreen( pScreen );
		}
		else
		{
			Width = 800;
			Height = 600;
		}

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );

		// TODO
		// Make sure the following Canvas items are valid
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.DepthStencil( FORMAT_D24S8 );
		m_Canvas.Colour( FORMAT_ARGB8 );

		m_pRenderer->GetXVisualInfo( m_Canvas, m_pDisplay, &pVI );

		ColourMap = XCreateColormap( m_pDisplay, RootWindow( m_pDisplay,
			pVI->screen ), pVI->visual, AllocNone );

		WinAttrs.colormap = ColourMap;
		WinAttrs.background_pixmap = None;
		WinAttrs.border_pixel = 0;
		WinAttrs.event_mask = StructureNotifyMask | ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, pVI->screen ),
			X, Y, Width, Height, 0, pVI->depth, InputOutput, pVI->visual,
			CWEventMask | CWColormap | CWBorderPixel, &WinAttrs );

		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );

		XStoreName( m_pDisplay, m_Window, g_pWindowTitle );
		XMoveWindow( m_pDisplay, m_Window, X, Y );
		XRaiseWindow( m_pDisplay, m_Window );

		m_pRenderer->SetWindow( m_Window );
		m_pRenderer->Create( m_Canvas );

		m_pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

		return D_OK;
	}

	D_UINT32 Game::Execute( )
	{
		return D_OK;
	}

	void Game::Update( const D_FLOAT64 p_ElapsedGameTime )
	{
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		m_pRenderer->EndScene( );
	}
}

