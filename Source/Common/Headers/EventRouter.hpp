#ifndef __DAWN_EVENTROUTER_HPP__
#define __DAWN_EVENTROUTER_HPP__

#include <DataTypes.hpp>
#include <Event.hpp>
#include <EventListener.hpp>
#include <queue>
#include <map>
#include <set>
#include <list>

namespace Dawn
{
	// NOTES:
	// For each system and sub-system the EventRouter is intended to route
	// events to their event listeners
	class EventRouter
	{
	public:
		~EventRouter( ) { }

		// Add and remove event listeners
		D_UINT32 Add( EventListener *p_pListener,
			const EventType &p_Type );
		D_UINT32 Remove( const EventListener *p_Listener );

		// Event passing functions
		D_UINT32 Send( const Event &p_Event );
		D_UINT32 Queue( const Event &p_Event,
			const D_FLOAT32 p_DeliveryTime = 0.0f );
		D_UINT32 Abort( const Event &p_Event,
			const D_BOOL p_AllOfType = D_FALSE );

		// Process the events in the queue
		D_UINT32 Tick( const D_UINT32 p_MaxTime = IEEE754_INFINITE32 );

		// Verify the event type is valid
		D_BOOL Verify( const EventType &p_Type ) const;

	private:
		// Event types are unique and only one of each need to persist
		typedef std::set< EventType > EventTypeSet;
		typedef std::pair< EventTypeSet::iterator, D_BOOL > EventTypeSetInsRes;
		
		// Track each event listener
		typedef std::list< EventListener * > EventListenerList;
		// Map an event ID to an event listener
		typedef std::map< D_UINT32, EventListenerList > EventListenerMap;
		typedef std::pair< D_UINT32, EventListenerList > EventListenerMapEntry;
		typedef std::pair< EventListenerMap::iterator, D_BOOL >
			EventListenerMapInsRes;

		// Keep a copy of the previous and current queue, so that events can be
		// processed in the previous queue and added to the current one for the
		// next update
		typedef std::queue< EventData * > EventQueue;

		// All of the unique types this router cares about
		EventTypeSet m_Types;
		// Mapping from the event IDs to the listeners this router will handle
		EventListenerMap m_EventRegistry;
		// An n-buffered queue
		EventQueue *m_pQueue;
		// Determines which event queue will be in use for the current update
		D_INT32 m_ActiveQueue;
	};
}

#endif
