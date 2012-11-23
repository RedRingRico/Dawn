#ifndef __DAWN_INPUTEVENTLISTENER_HPP__
#define __DAWN_INPUTEVENTLISTENER_HPP__

#include <EventListener.hpp>

namespace Dawn
{
	class InputEventListener : public EventListener
	{
#if ( BUILD_DEBUG || BUILD_PROFILE )
		virtual const char *GetName( ){ return "InputEventListner"; }
#endif
		virtual D_BOOL HandleEvent( const Event &p_Event );
	};
}

#endif

