#include <EventRouter.hpp>
#include <Time.hpp>

namespace Dawn
{
	EventRouter::EventRouter( const D_INT32 p_QueueCount ) :
		m_QueueCount( p_QueueCount ),
		m_ActiveQueue( 0 )
	{
		if( m_QueueCount <= 0 )
		{
			m_QueueCount = 1;
		}

		m_pQueue = new EventQueue[ m_QueueCount ];
	}

	EventRouter::~EventRouter( )
	{
		if( m_pQueue != D_NULL )
		{
			delete [ ] m_pQueue;
		}
	}

	D_UINT32 EventRouter::Add( EventListener *p_pListener,
		const EventType &p_Type )
	{
		if( this->Verify( p_Type ) != D_TRUE )
		{
			return D_ERROR;
		}
		
		// Check if this type is available
		EventTypeSet::iterator TSItr = m_Types.find( p_Type );
		
		// Add the type
		if( TSItr == m_Types.end( ) )
		{
			EventTypeSetInsRes IRes = m_Types.insert( p_Type );

			if( IRes.second == D_FALSE )
			{
				return D_ERROR;
			}

			// The list was left empty
			if( IRes.first == m_Types.end( ) )
			{
				return D_ERROR;
			}

			TSItr = IRes.first;
		}

		// Find the listener map entry
		EventListenerMap::iterator ELMItr =
			m_EventRegistry.find( p_Type.ID( ) );
		
		// Create it
		if( ELMItr == m_EventRegistry.end( ) )
		{
			EventListenerMapInsRes IRes = m_EventRegistry.insert(
				EventListenerMapEntry( p_Type.ID( ), EventListenerList( ) ) );
			
			if( IRes.second == D_FALSE )
			{
				return D_ERROR;
			}

			if( IRes.first == m_EventRegistry.end( ) )
			{
				return D_ERROR;
			}

			ELMItr = IRes.first;
		}

		EventListenerList &ELList = ( *ELMItr ).second;
		
		for( EventListenerList::iterator Itr = ELList.begin( ),
			ItrEnd = ELList.end( ); Itr != ItrEnd; ++Itr )
		{
			D_BOOL Match = ( *Itr == p_pListener );

			if( Match )
			{
				return D_ERROR;
			}
		}

		ELList.push_back( p_pListener );

		return D_OK;
	}

	D_UINT32 EventRouter::Remove( const EventListener *p_pListener )
	{
		D_UINT32 Return = D_ERROR;

		for( EventListenerMap::iterator Itr = m_EventRegistry.begin( ),
			ItrEnd = m_EventRegistry.end( ); Itr != ItrEnd; ++Itr )
		{
			EventListenerList &ELList = Itr->second;

			for( EventListenerList::iterator Itr2 = ELList.begin( ),
				ItrEnd2 = ELList.end( ); Itr2 != ItrEnd2; ++Itr2 )
			{
				// Found it!  Have it removed.
				if( *Itr2 == p_pListener )
				{
					ELList.erase( Itr2 );
					Return = D_OK;
					break;
				}
			}
		}

		return Return;
	}

	D_UINT32 EventRouter::Send( const Event &p_Event )
	{
		// Make sure this router will handle the event
		if( this->Verify( p_Event.Type( ) ) == D_FALSE )
		{
			return D_ERROR;
		}

		// Get a listener for the event
		EventListenerMap::const_iterator Itr = m_EventRegistry.find( 0 );

		if( Itr != m_EventRegistry.end( ) )
		{
			const EventListenerList &ELList = Itr->second;

			for( EventListenerList::const_iterator Itr2 = ELList.begin( ),
				ItrEnd2 = ELList.end( ); Itr2 != ItrEnd2; ++Itr2 )
			{
				( *Itr2 )->HandleEvent( p_Event );
			}
		}

		Itr = m_EventRegistry.find( p_Event.Type( ).ID( ) );

		if( Itr == m_EventRegistry.end( ) )
		{
			return D_ERROR;
		}

		const EventListenerList &ELList = Itr->second;

		D_BOOL EventProcessed = D_FALSE;

		for( EventListenerList::const_iterator Itr2 = ELList.begin( ),
			ItrEnd2 = ELList.end( ); Itr2 != ItrEnd2; ++Itr2 )
		{
			if( ( *Itr2 )->HandleEvent( p_Event ) == D_TRUE )
			{
				EventProcessed = D_TRUE;
			}
		}

		return EventProcessed;
	}

	D_UINT32 EventRouter::Queue( Event &p_Event,
		const D_FLOAT32 p_DeliveryTime )
	{
		if( this->Verify( p_Event.Type( ) ) != D_TRUE )
		{
			return D_ERROR;
		}

		if( m_ActiveQueue < 0 )
		{
			return D_ERROR;
		}
		if( m_ActiveQueue > m_QueueCount )
		{
			return D_ERROR;
		}

		if( p_DeliveryTime > 0.0f )
		{
			D_FLOAT32 TimeDelay = p_Event.Time( ) + p_DeliveryTime;
			p_Event.TimeDelay( TimeDelay );
		}

		EventListenerMap::const_iterator Itr =
			m_EventRegistry.find( p_Event.Type( ).ID( ) );

		// Try to match the event with a global listener
		if( Itr == m_EventRegistry.end( ) )
		{
			EventListenerMap::const_iterator Itr2 = m_EventRegistry.find( 0 );

			if( Itr2 == m_EventRegistry.end( ) )
			{
				return D_ERROR;
			}
		}

		m_pQueue[ m_ActiveQueue ].push_back( &p_Event );

		return D_OK;
	}

	D_UINT32 EventRouter::Abort( const EventType &p_Type,
		const D_BOOL p_AllOfType )
	{
		if( this->Verify( p_Type ) != D_TRUE )
		{
			return D_ERROR;
		}

		if( m_ActiveQueue < 0 )
		{
			return D_ERROR;
		}

		if( m_ActiveQueue > m_QueueCount )
		{
			return D_ERROR;
		}

		// Attempt to retrieve and remove the event from the queue
		EventListenerMap::iterator Itr =
			m_EventRegistry.find( p_Type.ID( ) );

		if( Itr == m_EventRegistry.end( ) )
		{
			return D_ERROR;
		}

		D_UINT32 Return = D_ERROR;

		for( EventQueue::iterator Itr2 = m_pQueue[ m_ActiveQueue ].begin( ),
			ItrEnd2 = m_pQueue[ m_ActiveQueue ].end( );
			Itr2 != ItrEnd2; ++Itr2 )
		{
			if( ( *Itr2 )->Type( ) == p_Type )
			{
				m_pQueue[ m_ActiveQueue ].erase( Itr2 );

				Return = D_OK;

				// Keep going?
				if( p_AllOfType == D_FALSE )
				{
					break;
				}
			}
		}

		return Return;
	}

	D_UINT32 EventRouter::Tick( const D_FLOAT32 p_MaxTime )
	{
		D_FLOAT32 CurrentTime = Dawn::GetTimeMS( );
		D_FLOAT32 MaxTime = ( p_MaxTime == IEEE754_INFINITE32 ) ?
			IEEE754_INFINITE32 : ( CurrentTime + p_MaxTime );
		// Use the current queue and empty ther next one
		D_INT32 CurrentQueue = m_ActiveQueue;

		m_ActiveQueue = ( m_ActiveQueue + 1 ) % m_QueueCount;

		m_pQueue[ m_ActiveQueue ].clear( );

		// Process as many events as possible within the maximum time slice
		while( m_pQueue[ CurrentQueue ].size( ) > 0 )
		{
			Event *pEvent = m_pQueue[ CurrentQueue ].front( );

			// As events are sorted by the timestamp + delay, any events after
			// this one should also not occur until after this event has been
			// fired
			if( pEvent->Time( ) + pEvent->TimeDelay( ) > Dawn::GetTimeMS( ) )
			{
				break;
			}

			m_pQueue[ CurrentQueue ].pop_front( );

			const EventType &Type = pEvent->Type( );

			EventListenerMap::const_iterator ListenItr =
				m_EventRegistry.find( Type.ID( ) );

			if( ListenItr != m_EventRegistry.end( ) )
			{
				const EventListenerList &List = ListenItr->second;

				for( EventListenerList::const_iterator Itr2 = List.begin( ),
					ItrEnd2 = List.end( ); Itr2 != ItrEnd2; ++Itr2 )
				{
					( *Itr2 )->HandleEvent( *pEvent );
				}
			}

			//Nothing is listening, keep going
			if( ListenItr == m_EventRegistry.end( ) )
			{
				continue;
			}

			const D_UINT32 ID = ListenItr->first;
			const EventListenerList &List = ListenItr->second;

			for( EventListenerList::const_iterator Itr2 = List.begin( ),
				ItrEnd2 = List.end( ); Itr2 != ItrEnd2; ++Itr2 )
			{
				if( ( *Itr2 )->HandleEvent( *pEvent ) == D_TRUE )
				{
					break;
				}
			}

			CurrentTime = Dawn::GetTimeMS( );

			if( p_MaxTime != IEEE754_INFINITE32 )
			{
				if( CurrentTime >= MaxTime )
				{
					// No time left!
					break;
				}
			}
		}

		// If there are still events to process, they will have to wait until
		// next time
		D_BOOL Flushed = ( m_pQueue[ CurrentQueue ].size( ) == 0 );

		if( Flushed == D_FALSE )
		{
			while( m_pQueue[ CurrentQueue ].size( ) > 0 )
			{
				Event *pEvent = m_pQueue[ CurrentQueue ].back( );
				m_pQueue[ CurrentQueue ].pop_back( );
				m_pQueue[ m_ActiveQueue ].push_front( pEvent );
			}
		}

		return D_OK;
	}

	D_BOOL EventRouter::Verify( const EventType &p_Type ) const
	{
		if( ( p_Type.ID( ) == 0 ) )
		{
			return D_FALSE;
		}

		EventTypeSet::const_iterator Itr = m_Types.find( p_Type );

		if( Itr != m_Types.end( ) )
		{
			const EventType &Known = *Itr;

			const D_UINT32 KnownID = Known.ID( );
			const D_UINT32 NewID = p_Type.ID( );

			D_BOOL Match = ( KnownID == NewID );

			if( Match != D_TRUE )
			{
				return D_FALSE;
			}
		}

		return D_TRUE;
	}
}
