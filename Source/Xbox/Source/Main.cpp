#include <xtl.h>
#include <XboxRenderer.hpp>

void Reboot( DWORD p_Menu );

void __cdecl main( )
{
	Dawn::XboxRenderer Renderer;
	Dawn::CanvasDescription Canvas;

	Canvas.Width( 640 );
	Canvas.Height( 480 );
	Canvas.Colour( FORMAT_ARGB8 );
	Canvas.DepthStencil( FORMAT_D24S8 );
	Canvas.BackBufferCount( 1 );

	if( Renderer.Create( Canvas ) != D_OK )
	{
		Reboot( XLD_LAUNCH_DASHBOARD_MAIN_MENU );
	}

	Renderer.SetClearColour( 0.15f, 0.0f, 0.15f );

	while( 1 )
	{
		Renderer.BeginScene( D_TRUE, D_TRUE, D_TRUE );
		Renderer.EndScene( );
	}
}


void Reboot( DWORD p_Menu )
{
	LD_LAUNCH_DASHBOARD LaunchData = { p_Menu };
	XLaunchNewImage( D_NULL, ( PLAUNCH_DATA )( &LaunchData ) );
}
