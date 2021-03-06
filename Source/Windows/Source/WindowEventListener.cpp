#include <WindowEventListener.hpp>
#include <Events.hpp>

namespace Dawn
{
	D_BOOL WindowEventListener::HandleEvent( const Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == g_EventWindowResizeID )
		{
			EventDataWindowResize *pData =
				p_Event.DataPtr< EventDataWindowResize >( );

			m_pRenderer->ResizeCanvas( pData->Width( ), pData->Height( ) );
		}

		return D_TRUE;
	}
}
