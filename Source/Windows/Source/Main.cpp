#include <Windows.h>
#include <Main.hpp>
#include <Game.hpp>

#include <EventRouter.hpp>

namespace Dawn
{
	class MyData : public EventData
	{
		D_UINT32 Int;
	};

	class MyEvent : public Event
	{
	public:
		MyEvent( ) :
		  Event( "MyEvent" )
		{
		}
	};

	class MyListener : public EventListener
	{
	public:
		D_EXPLICIT MyListener( ) { }

#if ( BUILD_DEBUG || BUILD_PROFILE )
		virtual const char *GetName( ){ return "A"; }
#endif
		virtual D_BOOL HandleEvent( const Event &p_Event )
		{
			return D_TRUE;
		}
	};
}

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_CmdLine, int p_CmdShow )
{
	Dawn::EventRouter TheRouter;
	Dawn::MyListener TheListener;
	Dawn::EventType TheType( "EventA" );
	Dawn::Event TheEvent( "EventA" );
	TheRouter.Add( &TheListener, TheType );
	TheRouter.Send( TheEvent );
	Dawn::Game MyGame;

	if( MyGame.Initialise( D_FALSE ) != D_OK )
	{
		return D_ERROR;
	}

	MyGame.Execute( );

	return 0;
}
