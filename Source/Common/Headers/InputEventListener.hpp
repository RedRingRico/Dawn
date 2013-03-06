#ifndef __DAWN_INPUTEVENTLISTENER_HPP__
#define __DAWN_INPUTEVENTLISTENER_HPP__

#include <EventListener.hpp>

namespace Dawn
{
	class InputEventListener : public EventListener
	{
#if ( ZED_BUILD_DEBUG || ZED_BUILD_PROFILE )
		virtual const char *GetName( ){ return "InputEventListner"; }
#endif
		virtual ZED_BOOL HandleEvent( const Event &p_Event );
	};
}

#endif

