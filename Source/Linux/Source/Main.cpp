#include <iostream>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	Dawn::Game TheGame;

	if( TheGame.Initialise( ZED_FALSE ) != ZED_OK )
	{
		return ZED_FAIL;
	}

	TheGame.Execute( );

	return ZED_OK;
}

