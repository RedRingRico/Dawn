#include <iostream>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	Dawn::Game TheGame;

	if( TheGame.Initialise( D_FALSE ) != D_OK )
	{
		return D_ERROR;
	}

	TheGame.Execute( );

	return D_OK;
}

