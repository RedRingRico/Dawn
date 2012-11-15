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
		D_EXPLICIT EventListener( ) { }
		virtual ~EventListener( ){ }

#if ( BUILD_DEBUG || BUILD_PROFILE )
		// Used for tracking the path an event takes
		virtual const char *GetName( ) = 0;
#endif

		// If an event was handled, return true, otherwise return false to let
		// another listener attempt to handle the event
		virtual D_BOOL HandleEvent(	const Event &p_Event ) = 0;
	};
}

#endif
