#include <Game.hpp>
#include <Events.hpp>
#include <LinuxRendererOGL3.hpp>
#include <LinuxWindow.hpp>

namespace Dawn
{
	Game::Game( )
	{
		m_pRenderer = ZED_NULL;
		m_pConfigFile = ZED_NULL;
		m_FullScreen = ZED_FALSE;
	}

	Game::~Game( )
	{
		if( m_pTriangle )
		{
			delete m_pTriangle;
			m_pTriangle = ZED_NULL;
		}
		if( m_pRenderer )
		{
			delete m_pRenderer;
			m_pRenderer = ZED_NULL;
		}

		if( m_pWindow )
		{
			delete m_pWindow;
			m_pWindow = ZED_NULL;
		}
	}

	ZED_UINT32 Game::Initialise( const ZED_BOOL p_FullScreen )
	{
		m_FullScreen = p_FullScreen;

		ZED_UINT32 X = 0, Y = 0, Width = 1280, Height = 800;
		// TODO
		// Attempt to create an OpenGL 3 renderer, then fall back to 2,
		// finally try to get an OpenGL 1 renderer
		m_pRenderer = new ZED::Renderer::LinuxRendererOGL3( );
		m_pWindow = new ZED::Renderer::LinuxWindow( );

		m_pWindow->Create( 0, 0, Width, Height );

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );

		// TODO
		// Make sure the following Canvas items are valid
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.DepthStencilFormat( ZED_FORMAT_D24S8 );
		m_Canvas.ColourFormat( ZED_FORMAT_ARGB8 );

		m_pRenderer->Create( /*ZED_NULL,*/ m_Canvas, ( *m_pWindow ) );

		m_pRenderer->ClearColour( 0.15f, 0.0f, 0.15f );

		Dawn::StartTime( );

		m_pTriangle = new Dawn::TriangleEntity( m_pRenderer );
		m_pTriangle->Initialise( );

		Dawn::StartTime( );

		m_pRenderer->SetRenderState( ZED_RENDERSTATE_CULLMODE,
			ZED_CULLMODE_CCW );
		m_pRenderer->SetRenderState( ZED_RENDERSTATE_DEPTH, ZED_ENABLE );
		m_pRenderer->SetClippingPlanes( 1.0f, 100000.0f );

		return ZED_OK;
	}


	ZED_UINT32 Game::Execute( )
	{
		XEvent m_Events;
		KeySym Key;
		m_Running = ZED_TRUE;
		ZED::Renderer::ZED_WINDOWDATA WinData = m_pWindow->WindowData( );
		ZED_UINT64 ElapsedTime = 0ULL;
		ZED_UINT64 TimeStep = 16667ULL;
		ZED_UINT64 OldTime = GetTimeMiS( );
		ZED_UINT64 FrameTime = GetTimeMiS( );
		ZED_MEMSIZE FrameRate = 0;

		ZED_UINT64 Accumulator = 0ULL;
		while( m_Running == ZED_TRUE )
		{
			while( XPending( WinData.pX11Display ) > 0 )
			{
				XNextEvent( WinData.pX11Display, &m_Events );
				switch( m_Events.type )
				{
					case KeyPress:
					{
						// Need to create some kind of EventInputKeyDown
						// and m_InputEvents.Send()
						Key = XLookupKeysym( &m_Events.xkey, 0 );
						if( Key == 'q' )
						{
							m_Running = ZED_FALSE;
						}
						break;
					}
					case ConfigureNotify:
					{
						Dawn::EventWindowResize Resize(
							m_Events.xconfigure.width,
							m_Events.xconfigure.height );/*
						m_WindowEvents.Send( Resize );*/
						break;
					}
					case EnterNotify:
					{
						XGrabKeyboard( WinData.pX11Display, WinData.X11Window,
							True, GrabModeAsync, GrabModeAsync, CurrentTime );
						XGrabPointer( WinData.pX11Display, WinData.X11Window,
							True, EnterWindowMask | LeaveWindowMask |
							PointerMotionMask, GrabModeAsync, GrabModeAsync,
							None, None, CurrentTime );
						
						break;
					}
					case LeaveNotify:
					{
						XUngrabKeyboard( WinData.pX11Display, CurrentTime );
						XUngrabPointer( WinData.pX11Display, CurrentTime );

						break;
					}
					default:
					{
						break;
					}
				}
			}
			const ZED_UINT64 NewTime = GetTimeMiS( );
			ZED_UINT64 DeltaTime = NewTime-OldTime;

			if( DeltaTime > 250000ULL )
			{
				DeltaTime = 250000ULL;
			}

			OldTime = NewTime;

			Accumulator += DeltaTime;

			if( Accumulator < 0ULL )
			{
				zedDebugBreak( );
			}

			while( Accumulator >= TimeStep )
			{
				this->Update( 0.0f );
				ElapsedTime += TimeStep;
				Accumulator -= TimeStep;
			}

			this->Render( );
			++FrameRate;

			if( ( NewTime - FrameTime ) >= 1000000ULL )
			{
				zedTrace( "FPS: %d\n", FrameRate );
				FrameTime = GetTimeMiS( );
				FrameRate = 0;
			}
		}
		return ZED_OK;
	}

	void Game::Update( const ZED_FLOAT64 p_ElapsedGameTime )
	{
		this->m_WindowEvents.Tick( 16.6667f );
		m_pTriangle->Update( );
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_pTriangle->Render( );
		m_pRenderer->EndScene( );
	}
}

