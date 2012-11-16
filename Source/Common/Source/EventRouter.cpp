#include <EventRouter.hpp>

namespace Dawn
{
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
