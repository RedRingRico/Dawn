#ifndef __DAWN_GAME_HPP__
#define __DAWN_GAME_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <VertexCache.hpp>
#include <CanvasDescription.hpp>
#include <EventRouter.hpp>
#include <WindowEventListener.hpp>
#include <cstdio>
#include <Shader.hpp>

#if ( ZED_PLATFORM_WINDOWS )
static const wchar_t *g_pWindowTitle =
#ifdef ZED_BUILD_DEBUG
	L"Dawn [DEBUG]";
#elif ZED_BUILD_PROFILE
	L"Dawn [PROFILE]";
#elif ZED_BUILD_RELEASE
	L"Dawn";
#endif
#elif ( ZED_PLATFORM_LINUX || ZED_PLATFORM_PANDORA )
static const char *g_pWindowTitle =
#ifdef ZED_BUILD_DEBUG
	"Dawn [DEBUG]";
#elif ZED_BUILD_PROFILE
	"Dawn [PROFILE]";
#elif ZED_BUILD_RELEASE
	"Dawn";
#endif
#endif


//#include <VertexCache.hpp>

namespace Dawn
{
	class Game
	{
	public:
		Game( );
		~Game( );

		ZED_UINT32 Initialise( const ZED_BOOL p_FullScreen = ZED_FALSE );
		void Update( const ZED_FLOAT64 p_ElapsedGameTime );
		void Render( );

		ZED_UINT32 Execute( );

		ZED_INLINE ZED_BOOL Running( ) const { return m_Running; }

	private:
#if ( ZED_PLATFORM_PANDORA || ZED_PLATFORM_LINUX )
		FILE	*m_pConfigFile;
		Display	*m_pDisplay;
		Window	m_Window;
		char *m_pWindowTitle;
#elif ( ZED_PLATFORM_XBOX || ZED_PLATFORM_WINDOWS )
		HANDLE m_ConfigFile;
#endif
#if ( ZED_PLATFORM_WINDOWS )
		HWND m_Window;
		HDC m_DeviceContext;
		wchar_t *m_pWindowTitle;

		static LRESULT CALLBACK WindowProc( HWND p_HWND, UINT p_Message,
			WPARAM p_WParam, LPARAM p_LParam );

		ZED_BOOL WindowProc( UINT p_Message, WPARAM p_WParam, LPARAM p_LParam );
#endif
		ZED_BOOL m_FullScreen;


		EventRouter m_WindowEvents;
		Dawn::WindowEventListener *m_pWindowEventListener;

		ZED_BOOL m_Running;

		ZED::Renderer::Renderer				*m_pRenderer;
		ZED::Renderer::CanvasDescription	m_Canvas;
		ZED::Renderer::VertexCache			*m_pCache;
		ZED::Renderer::Shader				*m_pShader;
		ZED::Renderer::Window				*m_pWindow;
	};
}

#endif

