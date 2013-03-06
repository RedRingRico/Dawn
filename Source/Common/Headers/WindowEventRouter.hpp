#ifndef __DAWN_WINDOWEVENTROUTER_HPP__
#define __DAWN_WINDOWEVENTROUTER_HPP__

#include <EventRouter.hpp>

namespace Dawn
{
	class WindowEventRouter : public EventRouter
	{
	public:
		ZED_EXPLICIT WindowEventRouter( );
		virtual ~WindowEventRouter( );

		virtual ZED_UINT32 Add( const EventListener &p_Listener );
		virtual ZED_UINT32 Remove( const EventListener &p_Listener );

		virtual ZED_UINT32 Send( const Event &p_Event );
		virtual ZED_UINT32 Queue( const Event &p_Event,
			const ZED_FLOAT32 p_DeliveryTime = 0.0f );
		virtual ZED_UINT32 Abort( const Event &p_Event,
			const ZED_BOOL p_AllOfType = ZED_FALSE );
		
		virtual ZED_UINT32 Tick( const ZED_FLOAT32 p_MaxTime );//= IEEE754_INFINITE32 );

		virtual ZED_UINT32 Verify( const EventType &p_Type ) const;
	};
}

#endif
