#include <Game.hpp>
#include <Events.hpp>
#include <WindowsRendererOGL1.hpp>
#include <Time.hpp>
#include <HgVersion.h>
#include <string>
#include <sstream>

namespace Dawn
{
	LRESULT CALLBACK WinProc( HWND p_HWND, UINT p_Message,
		WPARAM p_WParam, LPARAM p_LParam )
	{
		switch( p_Message )
		{
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
				break;
			}
		default:
			{
				return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
			}
		}
		return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
	}

	LRESULT CALLBACK Game::WindowProc( HWND p_HWND, UINT p_Message,
		WPARAM p_WParam, LPARAM p_LParam )
	{
		switch( p_Message )
		{
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
				break;
			}
		case WM_CLOSE:
			{
				PostQuitMessage( 0 );
				break;
			}
		default:
			return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
		}
		return 0L;
	}

	D_BOOL Game::WindowProc( UINT p_Message, WPARAM p_WParam, LPARAM p_LParam )
	{
		switch( p_Message )
		{
		case WM_DESTROY:
			{
				m_Running = D_FALSE;
				PostQuitMessage( 0 );
				break;
			}
		case WM_CLOSE:
			{
				PostQuitMessage( 0 );
				break;
			}
		case WM_MOVE:
		case WM_SIZE:
			{
				RECT NewSize;
				GetWindowRect( m_Window, &NewSize );

				EventWindowResize Resize( NewSize.right, NewSize.bottom );
				m_WindowEvents.Send( Resize );

				break;
			}
		default:
			break;
		}
		return D_TRUE;
	}

	Game::Game( )
	{
		m_Window = D_NULL;
		m_FullScreen = D_FALSE;
		m_pRenderer = D_NULL;
		m_DeviceContext = D_NULL;
		m_pWindowTitle = D_NULL;
	}

	Game::~Game( )
	{
		if( m_pWindowTitle )
		{
			delete m_pWindowTitle;
		}

		if( m_pWindowEventListener )
		{
			delete m_pWindowEventListener;
		}

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

		// Append the version to the base title
		std::wstringstream CompleteTitle;

		CompleteTitle << g_pWindowTitle << L" | Ver. " << 0 << L"." << 0 << 
			L"." << 0 << L"." << HG_REVISION << " [" << HG_CHANGESET << "]";

		m_pWindowTitle = new wchar_t[ CompleteTitle.str( ).size( ) + 1 ];

		wcsncpy( m_pWindowTitle, CompleteTitle.str( ).c_str( ),
			CompleteTitle.str( ).size( ) );
		m_pWindowTitle[ CompleteTitle.str( ).size( ) ] = '\0';

		memset( &WindowRect, 0, sizeof( RECT ) );

		WinClass.cbSize = sizeof( WNDCLASSEX );
		WinClass.cbClsExtra = 0;
		WinClass.cbWndExtra = 0;
		WinClass.hbrBackground = D_NULL;
		WinClass.hInstance = GetModuleHandle( D_NULL );
		WinClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
		WinClass.hIconSm = LoadIcon( NULL, IDI_WINLOGO );
		WinClass.hCursor = LoadCursor( NULL, IDC_ARROW );
		WinClass.lpfnWndProc = (WNDPROC)Game::WindowProc;
		WinClass.lpszClassName = m_pWindowTitle;
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

		m_Window = CreateWindowEx( ExStyle, m_pWindowTitle, m_pWindowTitle,
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

		// Start the global timer
		Dawn::StartTime( );

		// Set up the event listener for window events
		m_pWindowEventListener = new Dawn::WindowEventListener( m_pRenderer,
			m_Window );

		m_WindowEvents.Add( m_pWindowEventListener, g_EventTypeWindowResize );

		return D_OK;
	}

	void Game::Update( const D_FLOAT64 p_ElapsedGameTime )
	{
		this->m_WindowEvents.Tick( 16.6667f );
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		m_pRenderer->EndScene( );
	}

	D_UINT32 Game::Execute( )
	{
		D_BOOL Quit = D_FALSE;

		MSG Message;
		m_Running = D_TRUE;
		while( Quit == D_FALSE )
		{
			if( PeekMessage( &Message, D_NULL, 0, 0, PM_REMOVE ) )
			{
				if( Message.message == WM_QUIT )
				{
					Quit = D_TRUE;
				}
				else
				{
					TranslateMessage( &Message );
					DispatchMessage( &Message );
				}
			}
			else
			{
				this->Update( 0.0f );
				this->Render( );
			}
		}

		return D_OK;
	}
}
