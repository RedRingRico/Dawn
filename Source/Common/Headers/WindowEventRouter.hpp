#ifndef __DAWN_WINDOWEVENTROUTER_HPP__
#define __DAWN_WINDOWEVENTROUTER_HPP__

#include <EventRouter.hpp>

namespace Dawn
{
	class WindowEventRouter : public EventRouter
	{
	public:
		D_EXPLICIT WindowEventRouter( );
		virtual ~WindowEventRouter( );

		virtual D_UINT32 Add( const EventListener &p_Listener );
		virtual D_UINT32 Remove( const EventListener &p_Listener );

		virtual D_UINT32 Send( const Event &p_Event );
		virtual D_UINT32 Queue( const Event &p_Event,
			const D_FLOAT32 p_DeliveryTime = 0.0f );
		virtual D_UINT32 Abort( const Event &p_Event,
			const D_BOOL p_AllOfType = D_FALSE );
		
		virtual D_UINT32 Tick( const D_FLOAT32 p_MaxTime = IEEE754_INFINITE32 );

		virtual D_UINT32 Verify( const EventType &p_Type ) const;
	};
}

#endif
