#ifndef __DAWN_EVENTS_HPP__
#define __DAWN_EVENTS_HPP__

#include <Event.hpp>

namespace Dawn
{
	// Strings for the event types
	static char *g_pEventWindowResize = "Event::Window::Resize";

	// The hashes for the strings of the event types
	static D_UINT32 g_EventWindowResizeID = Dawn::Hash( g_pEventWindowResize );

	// The event types
	static EventType g_EventTypeWindowResize( g_pEventWindowResize );

	class EventDataWindowResize : public EventData
	{
	public:
		D_EXPLICIT EventDataWindowResize( const D_UINT32 p_Width,
			const D_UINT32 p_Height )
		{
			m_Width = p_Width;
			m_Height = p_Height;
		}

		const D_UINT32 Width( ) const { return m_Width; }
		const D_UINT32 Height( ) const { return m_Height; }

	private:
		D_UINT32 m_Width;
		D_UINT32 m_Height;
	};

	class EventWindowResize : public Event
	{
	public:
		EventWindowResize( const D_UINT32 p_Width, const D_UINT32 p_Height ) :
			Event( g_pEventWindowResize, 0.0f,
				new EventDataWindowResize( p_Width, p_Height ) )
		{}
	};
}

#endif
