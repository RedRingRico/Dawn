#include <LinuxRendererOGL1.hpp>
#include <X11/Xatom.h>
#include <iostream>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	Dawn::Game MyGame;

	MyGame.Initialise( );
	MyGame.Render( );

	sleep( 5 );

	return D_OK;
}

