#ifndef __DAWN_GAME_HPP__
#define __DAWN_GAME_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <EventRouter.hpp>
#include <WindowEventListener.hpp>
#include <cstdio>

#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
static const wchar_t *g_pWindowTitle =
#ifdef BUILD_DEBUG
	L"Dawn [DEBUG]";
#elif BUILD_PROFILE
	L"Dawn [PROFILE]";
#elif BUILD_RELEASE
	L"Dawn";
#endif
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 || PLATFORM_PANDORA )
static const char *g_pWindowTitle =
#ifdef BUILD_DEBUG
	"Dawn [DEBUG]";
#elif BUILD_PROFILE
	"Dawn [PROFILE]";
#elif BUILD_RELEASE
	"Dawn";
#endif
#endif


#include <VertexCache.hpp>

namespace Dawn
{
	class Game
	{
	public:
		Game( );
		~Game( );

		D_UINT32 Initialise( const D_BOOL p_FullScreen = D_FALSE );
		void Update( const D_FLOAT64 p_ElapsedGameTime );
		void Render( );

		D_UINT32 Execute( );

		D_BOOL Running( ) const { return m_Running; }

	private:
		Dawn::Renderer *m_pRenderer;
#if ( PLATFORM_PANDORA || PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
		FILE	*m_pConfigFile;
		Display	*m_pDisplay;
		Window	m_Window;
		char *m_pWindowTitle;
#elif ( PLATFORM_XBOX || PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		HANDLE m_ConfigFile;
#endif
#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		HWND m_Window;
		HDC m_DeviceContext;
		wchar_t *m_pWindowTitle;

		static LRESULT CALLBACK WindowProc( HWND p_HWND, UINT p_Message,
			WPARAM p_WParam, LPARAM p_LParam );

		D_BOOL WindowProc( UINT p_Message, WPARAM p_WParam, LPARAM p_LParam );
#endif
		D_BOOL m_FullScreen;
		Dawn::CanvasDescription m_Canvas;

		EventRouter m_WindowEvents;
		Dawn::WindowEventListener *m_pWindowEventListener;

		D_BOOL m_Running;

		Dawn::VertexCache *m_pCache;
	};
}

#endif

