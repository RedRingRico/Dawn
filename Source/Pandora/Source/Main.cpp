#include <iostream>
#include <OGLES2/GLES2Extender.hpp>
#include <PandoraRenderer.hpp>
#include <Game.hpp>
#include <string>
#include <sstream>

int main( int p_Argc, char **p_ppArgv )
{
	Display *pDisplay;
	Window XWindow;

	pDisplay = XOpenDisplay( D_NULL );

	if( pDisplay == D_NULL )
	{
		return 1;
	}

	XSetWindowAttributes WinAttr;
	WinAttr.border_pixel = 0;
	WinAttr.event_mask = StructureNotifyMask | ExposureMask |
		KeyPressMask | KeyReleaseMask |
		ButtonPressMask | ButtonReleaseMask;
	
	XWindow = XCreateWindow( pDisplay, DefaultRootWindow( pDisplay ),
		0, 0, 800, 480, 0,
		CopyFromParent, InputOutput, CopyFromParent,
		CWEventMask | CWBorderPixel,
		&WinAttr );

	XMapWindow( pDisplay, XWindow );
	XMapRaised( pDisplay, XWindow );
	std::stringstream CompleteTitle;

	CompleteTitle << g_pWindowTitle << " | Ver. " << 0 << "." << 0 << "." << 0
		<< "." << HG_REVISION << " [" << HG_CHANGESET << "]";
	XStoreName( pDisplay, XWindow, CompleteTitle.str( ).c_str( ) );

	Dawn::CanvasDescription Canvas;

	Canvas.Width( 800 );
	Canvas.Height( 480 );
	Canvas.BackBufferCount( 1 );
	Canvas.Colour( FORMAT_ARGB8 );
	Canvas.DepthStencil( FORMAT_D24S8 );

	Dawn::PandoraRenderer *pRenderer = new Dawn::PandoraRenderer( );

	pRenderer->SetDisplay( pDisplay );
	pRenderer->SetWindow( XWindow );
	pRenderer->Create( Canvas );
	pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

	XEvent Event;
	KeySym Key;
	D_BOOL Quit = D_FALSE;
	while( Quit == D_FALSE )
	{
		while( XPending( pDisplay ) > 0 )
		{
			XNextEvent( pDisplay, &Event );
			switch( Event.type )
			{
				case KeyPress:
				{
					Key = XLookupKeysym( &Event.xkey, 0 );
					switch( Key )
					{
						case XK_Escape:
						{
							Quit = D_TRUE;
							break;
						}
					}
					break;
				}

				case ConfigureNotify:
				{
					pRenderer->ResizeCanvas( Event.xconfigure.width,
						Event.xconfigure.height );
					break;
				}
			}
		}
		pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		pRenderer->EndScene( );
	}

	delete pRenderer;

	XDestroyWindow( pDisplay, XWindow );
	XCloseDisplay( pDisplay );

	return 0;
}

