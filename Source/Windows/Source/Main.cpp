#include <Windows.h>
#include <Main.hpp>
#include <Game.hpp>

#include <Hash.hpp>
#include <Event.hpp>

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_CmdLine, int p_CmdShow )
{
	Dawn::Game MyGame;

	if( MyGame.Initialise( D_FALSE ) != D_OK )
	{
		return D_ERROR;
	}

	MyGame.Execute( );

	return 0;
}
