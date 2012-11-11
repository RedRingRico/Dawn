#include <Game.hpp>
#include <WindowsRendererOGL1.hpp>

namespace Dawn
{
	LRESULT CALLBACK WndProc( HWND p_HWND, UINT p_Message, WPARAM p_WParam,
		LPARAM p_LParam )
	{
		return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
	}

	Game::Game( )
	{
		m_Window = D_NULL;
		m_FullScreen = D_FALSE;
		m_pRenderer = D_NULL;
		m_DeviceContext = D_NULL;
	}

	Game::~Game( )
	{
		if( m_pRenderer )
		{
			delete m_pRenderer;
		}

		if( m_FullScreen == D_TRUE )
		{
			ChangeDisplaySettings( D_NULL, 0 );
			ShowCursor( TRUE );
		}

		if( m_DeviceContext != D_NULL )
		{
			ReleaseDC( m_Window, m_DeviceContext );
			m_DeviceContext = D_NULL;
		}

		if( m_Window != D_NULL )
		{
			DestroyWindow( m_Window );
			m_Window = D_NULL;
			UnregisterClass( g_pWindowTitle, GetModuleHandle( D_NULL ) );
		}
	}

	D_UINT32 Game::Initialise( const D_BOOL p_FullScreen )
	{
		WNDCLASSEX WinClass;
		DWORD Style = 0, ExStyle = 0;
		RECT WindowRect;
		D_UINT32 X = 0, Y = 0, Width = 0, Height = 0;
		HWND DesktopWindow = D_NULL;
		HDC DesktopDC = D_NULL;

		memset( &WindowRect, 0, sizeof( RECT ) );

		WinClass.cbSize = sizeof( WNDCLASSEX );
		WinClass.cbClsExtra = 0;
		WinClass.cbWndExtra = 0;
		WinClass.hbrBackground = D_NULL;
		WinClass.hInstance = GetModuleHandle( D_NULL );
		WinClass.hIcon = D_NULL;
		WinClass.hIconSm = D_NULL;
		WinClass.hCursor = D_NULL;
		WinClass.lpfnWndProc = (WNDPROC)WndProc;
		WinClass.lpszClassName = g_pWindowTitle;
		WinClass.lpszMenuName = D_NULL;
		WinClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if( !RegisterClassEx( &WinClass ) )
		{
			return D_ERROR;
		}

		DesktopWindow = GetDesktopWindow( );
		DesktopDC = GetDC( DesktopWindow );

		m_FullScreen = p_FullScreen;

		if( m_FullScreen == D_TRUE )
		{
			Width = GetDeviceCaps( DesktopDC, HORZRES );
			Height = GetDeviceCaps( DesktopDC, VERTRES );
			WindowRect.left = 0L;
			WindowRect.right = static_cast< long >( Width );

			WindowRect.top = 0L;
			WindowRect.bottom = static_cast< long >( Height );

			DEVMODE ScreenSettings;
			memset( &ScreenSettings, 0, sizeof( DEVMODE ) );
			ScreenSettings.dmSize = sizeof( DEVMODE );
			ScreenSettings.dmPelsWidth = Width;
			ScreenSettings.dmPelsHeight = Height;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH |
				DM_PELSHEIGHT;

			if( ChangeDisplaySettings( &ScreenSettings, CDS_FULLSCREEN ) !=
				DISP_CHANGE_SUCCESSFUL )
			{
				return D_ERROR;
			}

			ExStyle = WS_EX_APPWINDOW;
			Style = WS_POPUP;

			ShowCursor( FALSE );
		}
		else
		{
			D_FLOAT32 WidthF = 0.0f, HeightF = 0.0f;
			D_FLOAT32 XF = 0.0f, YF = 0.0f;

			WidthF = static_cast< D_FLOAT32 >(
				GetDeviceCaps( DesktopDC, HORZRES ) );
			HeightF = static_cast< D_FLOAT32 >(
				GetDeviceCaps( DesktopDC, VERTRES ) );

			
			XF = ( WidthF / 100.0f ) * 5.0f;
			YF = ( HeightF / 100.0f ) * 5.0f;
			WidthF = ( WidthF / 100.0f ) * 90.0f;
			HeightF = ( HeightF / 100.0f ) * 90.0f;

			X = static_cast< D_UINT32 >( XF );
			Y = static_cast< D_UINT32 >( YF );
			Width = static_cast< D_UINT32 >( WidthF );
			Height = static_cast< D_UINT32 >( HeightF );

			WindowRect.left = 0L;
			WindowRect.right = static_cast< long >( Width );

			WindowRect.top = 0L;
			WindowRect.bottom = static_cast< long >( Height );

			ExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			Style = WS_OVERLAPPEDWINDOW;
		}

		ReleaseDC( DesktopWindow, DesktopDC );
		AdjustWindowRectEx( &WindowRect, Style, FALSE, ExStyle );

		m_Window = CreateWindowEx( ExStyle, g_pWindowTitle, g_pWindowTitle,
			Style, X, Y, Width, Height, D_NULL, D_NULL,
			GetModuleHandle( D_NULL ), D_NULL );

		DWORD Err = GetLastError( );

		if( m_Window == D_NULL )
		{
			return D_ERROR;
		}

		m_pRenderer = new Dawn::WindowsRendererOGL1( );

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.DepthStencil( FORMAT_D24S8 );
		m_Canvas.Colour( FORMAT_ARGB8 );

		m_DeviceContext = GetDC( m_Window );

		m_pRenderer->Create( m_Canvas, m_DeviceContext );

		m_pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

		ShowWindow( m_Window, SW_SHOW );
		SetForegroundWindow( m_Window );
		SetFocus( m_Window );

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
