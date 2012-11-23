#ifndef __DAWN_EVENTS_HPP__
#define __DAWN_EVENTS_HPP__

#include <Event.hpp>
#include <Input.hpp>

namespace Dawn
{
	// Strings for the event types
	// -- WINDOW SYSTEM --
	static char *g_pEventWindowResize = "Event::Window::Resize";
	// -- INPUT --
	static char *g_pEventInputKeyDown = "Event::Input::KeyDown";

	// The hashes for the strings of the event types
	// -- WINDOW SYSTEM --
	static D_UINT32 g_EventWindowResizeID = Dawn::Hash( g_pEventWindowResize );
	// --INPUT --
	static D_UINT32 g_EventInputKeyDownID = Dawn::Hash( g_pEventInputKeyDown );

	// The event types
	// -- WINDOW SYSTEM --
	static EventType g_EventTypeWindowResize( g_pEventWindowResize );
	// -- INPUT --
	static EventType g_EventTypeInputKeyDown( g_pEventInputKeyDown );

	// Event Data
	// -- WINDOW SYSTEM --
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

	// Events
	// -- WINDOW SYSTEM --
	class EventWindowResize : public Event
	{
	public:
		EventWindowResize( const D_UINT32 p_Width, const D_UINT32 p_Height ) :
			Event( g_pEventWindowResize, 0.0f,
				new EventDataWindowResize( p_Width, p_Height ) )
		{}
	};

	// -- INPUT --
	class EventInputKeyDown : public Event
	{
	public:
	};
}

#endif
