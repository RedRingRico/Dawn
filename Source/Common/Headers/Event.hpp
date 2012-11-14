#ifndef __DAWN_EVENT_HPP__
#define __DAWN_EVENT_HPP__

#include <DataTypes.hpp>
#include <Hash.hpp>

namespace Dawn
{
	// Events are sent on a per-subsystem basis
	class Event
	{
	public:
		D_EXPLICIT Event( const char * const p_pIDString ) :
			m_ID( Dawn::Hash( p_pIDString ) ),
			m_pIDString( p_pIDString )
		{
		}

		D_UINT32 ID( ) const
		{
			return m_ID;
		}

		const char * const IDString( ) const
		{
			return m_pIDString;
		}

		D_BOOL operator==( Event const &p_Other )
		{
			if( p_Other.m_ID == this->m_ID )
			{
				return D_TRUE;
			}

			return D_FALSE;
		}

	private:
		D_UINT32	m_ID;
		const char	*m_pIDString;
	};
}

#endif
