#ifndef __DAWNGAME_HPP__
#define __DAWNGAME_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
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
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
static const char *g_pWindowTitle =
#ifdef BUILD_DEBUG
	"Dawn [DEBUG]";
#elif BUILD_PROFILE
	"Dawn [PROFILE]";
#elif BUILD_RELEASE
	"Dawn";
#endif
#endif

namespace Dawn
{
	class Game
	{
	public:
		Game( );
		~Game( );

		D_UINT32 Initialise( );
		void Update( const D_FLOAT64 p_ElapsedGameTime );
		void Render( );

		bool Running( );

	private:
		Dawn::Renderer *m_pRenderer;
#if ( PLATFORM_PANDORA || PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
		FILE	*m_pConfigFile;
		Display	*m_pDisplay;
		Window	m_Window;
#elif ( PLATFORM_XBOX || PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		HANDLE m_ConfigFile;
#endif
		D_BOOL m_FullScreen;
		Dawn::CanvasDescription m_Canvas;
	};
}

#endif

