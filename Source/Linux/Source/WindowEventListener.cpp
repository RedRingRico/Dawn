#include <WindowEventListener.hpp>
#include <iostream>
#include <Events.hpp>

namespace Dawn
{
	ZED_BOOL WindowEventListener::HandleEvent(
		const ZED::System::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == g_EventWindowResizeID )
		{
			EventDataWindowResize *pData =
				p_Event.Data< EventDataWindowResize >( );

			m_pRenderer->ResizeCanvas( pData->Width( ), pData->Height( ) );

			return ZED_TRUE;
		}
		
		return ZED_FALSE;
	}
}

