#include <LinuxRendererOGL1.hpp>
#include <X11/Xatom.h>

const char *g_pWindowTitle =
#ifdef BUILD_DEBUG
"Dawn [DEBUG]";
#elif BUILD_PROFILE
"Dawn [PROFILE]";
#else
"Dawn";
#endif

D_BOOL g_Quit;

int main( int p_Argc, char **p_ppArgv )
{
	Dawn::LinuxRendererOGL1 *pRenderer = new Dawn::LinuxRendererOGL1( );
	Screen *pScreen = NULL;
	Display *pDisplay = XOpenDisplay( 0 );
	pScreen = DefaultScreenOfDisplay( pDisplay );

	D_INT32 X, Y, Width, Height;
	Width = WidthOfScreen( pScreen );
	Height = HeightOfScreen( pScreen );

	// Position the window centred and make the window size 90%
	// of the total screen resolution
	{
		D_FLOAT32 WidthF = ( D_FLOAT32 )( Width );
		D_FLOAT32 HeightF = ( D_FLOAT32 )( Height );
		D_FLOAT32 XF, YF;

		XF = ( WidthF / 100.0f ) * 5.0f;
		YF = ( HeightF / 100.0f ) * 5.0f;

		WidthF = ( WidthF / 100.0f ) * 90.0f;
		HeightF = ( HeightF / 100.0f ) * 90.0f;

		X = ( D_INT32 )( XF );
		Y = ( D_INT32 )( YF );
		Width = ( D_INT32 )( WidthF );
		Height = ( D_INT32 )( HeightF );
	}

	XVisualInfo *pVI;

	Dawn::CanvasDescription Canvas;

	Canvas.Width( Width );
	Canvas.Height( Height );
	Canvas.BackBufferCount( 1 );
	Canvas.DepthStencil( FORMAT_D24S8 );
	Canvas.Colour( FORMAT_ARGB8 );

	pRenderer->GetXVisualInfo( Canvas, pDisplay, &pVI );

	Colormap CMap = XCreateColormap( pDisplay,
		RootWindow( pDisplay, pVI->screen ), pVI->visual,
		AllocNone );
	
	XSetWindowAttributes WinAttr;

	WinAttr.colormap = CMap;
	WinAttr.background_pixmap = None;
	WinAttr.border_pixel = 0;
	WinAttr.event_mask = StructureNotifyMask | ExposureMask |
		KeyPressMask | KeyReleaseMask | ButtonPressMask |
		ButtonReleaseMask | ResizeRedirectMask | PointerMotionMask;

	Window XWin = XCreateWindow( pDisplay,
		RootWindow( pDisplay, pVI->screen ),
		X, Y, Width, Height,
		0, pVI->depth, InputOutput, pVI->visual,
		CWEventMask|CWColormap|CWBorderPixel, &WinAttr );

	XMapWindow( pDisplay, XWin );
	XMapRaised( pDisplay, XWin );

	XStoreName( pDisplay, XWin, g_pWindowTitle );
	XMoveWindow( pDisplay, XWin, X, Y );
	XRaiseWindow( pDisplay, XWin );

	pRenderer->SetWindow( XWin );
	pRenderer->Create( Canvas );
	pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

	XSync( pDisplay, False );

	g_Quit = false;
	XEvent Events;
	KeySym Key;

	while( g_Quit != true )
	{
		while( XPending( pDisplay ) > 0 )
		{
			XNextEvent( pDisplay, &Events );
			switch( Events.type )
			{
				case KeyPress:
				{
					Key = XLookupKeysym( &Events.xkey, 0 );
					if( Key == 'q' )
					{
						g_Quit = true;
					}
					break;
				}
			}
		}

		pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		pRenderer->EndScene( );
	}

	delete pRenderer;

	XDestroyWindow( pDisplay, XWin );
	XCloseDisplay( pDisplay );

	return 0;
}

