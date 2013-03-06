#ifndef __DAWN_EVENTLISTENER_HPP__
#define __DAWN_EVENTLISTENER_HPP__

#include <DataTypes.hpp>
#include <Event.hpp>

namespace Dawn
{
	// NOTES:
	// EventListener is a base class which the EventRouter will be using to
	// correctly pass events along
	class EventListener
	{
	public:
		// There should not be any way to initialise a non-concrete instance
		ZED_EXPLICIT EventListener( ) { }
		virtual ~EventListener( ){ }

#if ( ZED_BUILD_DEBUG || ZED_BUILD_PROFILE )
		// Used for tracking the path an event takes
		virtual const char *GetName( ) = 0;
#endif

		// If an event was handled, return true, otherwise return false to let
		// another listener attempt to handle the event
		virtual ZED_BOOL HandleEvent(	const Event &p_Event ) = 0;
	};
}

#endif
