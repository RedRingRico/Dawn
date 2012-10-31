#include <Windows.h>
#include <WindowsRendererOGL1.hpp>

LRESULT CALLBACK WinProc( HWND p_HWND, UINT p_Message, WPARAM p_WParam,
	LPARAM p_LParam );

const LPCWSTR g_pAppName =
#if BUILD_DEBUG
L"Dawn [DEBUG]";
#elif BUILD_PROFILE
L"Dawn [PROFILE]";
#else
L"Dawn";
#endif

D_BOOL g_Quit;

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_CmdLine, int p_CmdShow )
{
	WNDCLASSEX WinClass;
	WinClass.cbSize = sizeof( WNDCLASSEX );
	WinClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WinClass.cbClsExtra = 0;
	WinClass.cbWndExtra = 0;
	WinClass.hInstance = p_ThisInst;
	WinClass.hbrBackground = NULL;
	WinClass.lpszClassName = g_pAppName;
	WinClass.lpfnWndProc = ( WNDPROC )WinProc;
	WinClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	WinClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	WinClass.lpszMenuName = NULL;
	WinClass.hIconSm = NULL;

	if( !RegisterClassEx( &WinClass ) )
	{
		return 1;
	}

	// Create a window which is 90% of the main monitor's resolution and
	// centre it
	DWORD Style, ExStyle;
	RECT WindowRect;
	D_UINT32 Width, Height, X, Y;
	HWND DesktopWindow = GetDesktopWindow( );
	HDC DesktopDC = GetDC( DesktopWindow );
	Width = ( GetDeviceCaps( DesktopDC, HORZRES ) / 100 ) * 90;
	Height = ( GetDeviceCaps( DesktopDC, VERTRES ) / 100 ) * 90;
	X = ( GetDeviceCaps( DesktopDC, HORZRES ) / 100 ) * 5;
	Y = ( GetDeviceCaps( DesktopDC, VERTRES ) / 100 ) * 5;

	WindowRect.left = ( long )0;
	WindowRect.right = ( long )Width;
	WindowRect.top = ( long )0;
	WindowRect.bottom = ( long )Height;
	ExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	Style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx( &WindowRect, Style, FALSE, ExStyle );

	HWND Window = CreateWindowEx( ExStyle, g_pAppName, g_pAppName, Style, X, Y,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL, NULL, p_ThisInst, NULL );

	if( Window == NULL )
	{
		return D_ERROR;
	}

	// Associate the renderer with the window
	Dawn::CanvasDescription Canvas;
	memset( &Canvas, 0, sizeof( Canvas ) );
	Canvas.BackBufferCount( 1 );
	Canvas.Width( WindowRect.right );
	Canvas.Height( WindowRect.bottom );
	Canvas.Colour( FORMAT_ARGB8 );
	Canvas.DepthStencil( FORMAT_D24S8 );

	Dawn::WindowsRendererOGL1 OGLRenderer;
	HDC WinDC = GetDC( Window );
	if( OGLRenderer.Create( Canvas, WinDC ) != D_OK )
	{
		return D_ERROR;
	}

	OGLRenderer.SetClearColour( 0.15f, 0.0f, 0.15f );

	MSG Message;
	g_Quit = D_FALSE;

	ShowWindow( Window, SW_SHOW );
	SetForegroundWindow( Window );
	SetFocus( Window );

	while( g_Quit == D_FALSE )
	{
		while( PeekMessage( &Message, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( GetMessage( &Message, NULL, 0, 0 ) )
			{
				TranslateMessage( &Message );
				DispatchMessage( &Message );
			}
			else
			{
				if( Message.message == WM_CLOSE )
				{
					g_Quit = D_TRUE;
				}
			}
		}
		OGLRenderer.BeginScene( D_TRUE, D_TRUE, D_TRUE );
		OGLRenderer.EndScene( );
	}

	return 0;
}

LRESULT CALLBACK WinProc( HWND p_HWND, UINT p_Message, WPARAM p_WParam,
	LPARAM p_LParam )
{
	switch( p_Message )
	{
	case WM_SYSCOMMAND:
		{
			switch( p_WParam )
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				{
					return 0L;
				}
			case SC_CLOSE:
				{
					g_Quit = D_TRUE;
				}
			}
			break;
		}
	case WM_KEYDOWN:
		{
			if( p_WParam == VK_ESCAPE )
			{
				g_Quit = D_TRUE;
			}
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			g_Quit = D_TRUE;
			break;
		}
	default:
		return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
	}

	return 0L;
}
