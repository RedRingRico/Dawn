#ifndef __DAWN_WINDOWEVENTLISTENER_HPP__
#define __DAWN_WINDOWEVENTLISTENER_HPP__

#include <EventListener.hpp>
#include <Renderer.hpp>

namespace Dawn
{
	class WindowEventListener : public EventListener
	{
	public:
#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		D_EXPLICIT WindowEventListener( Renderer *p_pRenderer,
			const HWND &p_HWND ) :
			m_pRenderer( p_pRenderer ), m_HWND( p_HWND )
		{ }
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
		D_EXPLICIT WindowEventListener( Renderer *p_pRenderer,
			Display *p_pDisplay ) :
			m_pRenderer( p_pRenderer ), m_pDisplay( p_pDisplay )
		{ }
#endif
		virtual ~WindowEventListener( ) { }

#if ( BUILD_DEBUG || BUILD_PROFILE )
		virtual const char *GetName( ){ return "WindowEventListener"; }
#endif
		virtual D_BOOL HandleEvent( const Event &p_Event );

	private:
		Renderer *m_pRenderer;

#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		HWND m_HWND;
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
		Display *m_pDisplay;
#endif
	};
}

#endif
