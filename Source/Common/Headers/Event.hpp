#ifndef __DAWN_EVENT_HPP__
#define __DAWN_EVENT_HPP__

#include <DataTypes.hpp>
#include <Hash.hpp>
#include <Time.hpp>

namespace Dawn
{
	// NOTES:
	// Events should be sent on a per-subsystem basis
	class EventType
	{
	public:
		ZED_EXPLICIT EventType( const char * const p_pIDString ) :
			m_ID( Dawn::Hash( p_pIDString ) ),
			m_pIDString( p_pIDString )
		{
		}

		ZED_UINT32 ID( ) const
		{
			return m_ID;
		}

		const char * const IDString( ) const
		{
			return m_pIDString;
		}

		ZED_BOOL operator<( const EventType &p_Other ) const
		{
			return ( m_ID < p_Other.m_ID );
		}

		ZED_BOOL operator==( const EventType &p_Other ) const
		{
			if( p_Other.m_ID == this->m_ID )
			{
				return ZED_TRUE;
			}

			return ZED_FALSE;
		}

	private:
		// The hashed version of the ID
		ZED_UINT32	m_ID;
		// ID in its raw form (much less runtime-friendly)
		const char	*m_pIDString;
	};

	// NOTES:
	// Used as a base class for real data to be re-interpreted as
	class EventData
	{
	public:
		virtual ~EventData( ){ }
	};

	// NOTES:
	// An Event is a composite which consists of a timestamp as to when the
	// event was generated and 
	class Event
	{
	public:
		ZED_EXPLICIT Event( const char * const p_pEventName,
			ZED_FLOAT32 p_TimeStamp = ZED::System::GetTimeMS( ),
			EventData *p_pData = ZED_NULL ) :
			m_Type( p_pEventName ),
			m_pData( p_pData ),
			m_TimeStamp( p_TimeStamp ),
			m_TimeDelay( 0.0f )
		{
		}

		virtual ~Event( ){ }

		// Identify which type of event this is
		const EventType &Type( ) const { return m_Type; }
		// Get the data as an non-typed object
		const EventData *Data( ) const { return m_pData; }

		const ZED_FLOAT32 Time( ) const { return m_TimeStamp; }

		// Time delay manipulator and accessor
		void TimeDelay( const ZED_FLOAT32 p_TimeDelay )
			{ m_TimeDelay = p_TimeDelay; }
		const ZED_FLOAT32 TimeDelay( ) const { return m_TimeDelay; }

		// Get the real data
		template< typename T > T *DataPtr( ) const
		{
			return reinterpret_cast< T * >( m_pData );
		}

		const ZED_BOOL operator<( const Event &p_Other ) const
		{
			if( ( m_TimeDelay + m_TimeStamp ) <
				( p_Other.m_TimeDelay + p_Other.m_TimeStamp ) )
			{
				return ZED_TRUE;
			}
			return ZED_FALSE;
		}

	private:
		// Type is unique and it should be very slim to have two similar event
		// types registered which are intended to be different
		EventType	m_Type;
		// The data which the event will provide to be consumed by an event
		// listener
		EventData *m_pData;
		// Time at which the event was generated
		ZED_FLOAT32	m_TimeStamp;
		// Offset for delaying the delivery of the event
		ZED_FLOAT32	m_TimeDelay;
	};
}

#endif
