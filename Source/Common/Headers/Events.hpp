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
	static ZED_UINT32 g_EventWindowResizeID = Dawn::Hash( g_pEventWindowResize );
	// --INPUT --
	static ZED_UINT32 g_EventInputKeyDownID = Dawn::Hash( g_pEventInputKeyDown );

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
		ZED_EXPLICIT EventDataWindowResize( const ZED_UINT32 p_Width,
			const ZED_UINT32 p_Height )
		{
			m_Width = p_Width;
			m_Height = p_Height;
		}

		const ZED_UINT32 Width( ) const { return m_Width; }
		const ZED_UINT32 Height( ) const { return m_Height; }

	private:
		ZED_UINT32 m_Width;
		ZED_UINT32 m_Height;
	};

	// Events
	// -- WINDOW SYSTEM --
	class EventWindowResize : public Event
	{
	public:
		EventWindowResize( const ZED_UINT32 p_Width, const ZED_UINT32 p_Height ) :
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
