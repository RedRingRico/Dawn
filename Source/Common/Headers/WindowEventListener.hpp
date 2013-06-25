#ifndef __DAWN_WINDOWEVENTLISTENER_HPP__
#define __DAWN_WINDOWEVENTLISTENER_HPP__

#include <System/Event.hpp>
#include <System/EventRouter.hpp>
#include <Renderer.hpp>

namespace Dawn
{
	class WindowEventListener : public ZED::System::EventListener
	{
	public:
#if ( ZED_PLATFORM_WINDOWS )
		ZED_EXPLICIT WindowEventListener( ZED::Renderer::Renderer *p_pRenderer,
			const HWND &p_HWND ) :
			m_pRenderer( p_pRenderer ), m_HWND( p_HWND )
		{ }
#elif ( ZED_PLATFORM_LINUX )
		ZED_EXPLICIT WindowEventListener( ZED::Renderer::Renderer *p_pRenderer,
			Display *p_pDisplay ) :
			m_pRenderer( p_pRenderer ), m_pDisplay( p_pDisplay )
		{ }
#endif
		virtual ~WindowEventListener( ) { }

#if ( ZED_BUILD_DEBUG || ZED_BUILD_PROFILE )
		virtual const char *GetName( ){ return "WindowEventListener"; }
#endif
		virtual ZED_BOOL HandleEvent( const ZED::System::Event &p_Event );

	private:
		ZED::Renderer::Renderer *m_pRenderer;

#if ( ZED_PLATFORM_WINDOWS )
		HWND m_HWND;
#elif ( ZED_PLATFORM_LINUX )
		Display *m_pDisplay;
#endif
	};
}

#endif
