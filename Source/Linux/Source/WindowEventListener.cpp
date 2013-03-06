#include <WindowEventListener.hpp>
#include <Events.hpp>
#include <iostream>

namespace Dawn
{
	ZED_BOOL WindowEventListener::HandleEvent( const Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == g_EventWindowResizeID )
		{
			EventDataWindowResize *pData =
				p_Event.DataPtr< EventDataWindowResize >( );

			m_pRenderer->ResizeCanvas( pData->Width( ), pData->Height( ) );

			return ZED_TRUE;
		}
		
		return ZED_FALSE;
	}
}

