#include <LinuxRendererOGL1.hpp>
#include <iostream>
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

#ifdef BUILD_DEBUG
		std::cout << "X: " << X << std::endl;
		std::cout << "Y: " << Y << std::endl;
		std::cout << "Width: " << Width << std::endl;
		std::cout << "Height: " << Height << std::endl;
#endif
	}

	XSetWindowAttributes WinAttr;

	WinAttr.event_mask = StructureNotifyMask | ExposureMask |
		KeyPressMask | KeyReleaseMask | ButtonPressMask |
		ButtonReleaseMask | ResizeRedirectMask | PointerMotionMask;

	Window XWin = XCreateWindow( pDisplay, DefaultRootWindow( pDisplay ),
		X, Y, Width, Height,
		0, CopyFromParent, InputOutput, CopyFromParent,
		CWEventMask, &WinAttr );

	XMapWindow( pDisplay, XWin );
	XMapRaised( pDisplay, XWin );

	XStoreName( pDisplay, XWin, g_pWindowTitle );
	XMoveWindow( pDisplay, XWin, X, Y );

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
	}

	XDestroyWindow( pDisplay, XWin );
	XCloseDisplay( pDisplay );

	return 0;
}

