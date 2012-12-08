#include <xtl.h>
#include <Game.hpp>

void Reboot( DWORD p_Menu );

void __cdecl main( )
{
	Dawn::Game TheGame;

	if( TheGame.Initialise( ) != D_OK )
	{
		Reboot( XLD_LAUNCH_DASHBOARD_MAIN_MENU );
	}

	TheGame.Execute( );
}


void Reboot( DWORD p_Menu )
{
	LD_LAUNCH_DASHBOARD LaunchData = { p_Menu };
	XLaunchNewImage( D_NULL, ( PLAUNCH_DATA )( &LaunchData ) );
}
