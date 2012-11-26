#include <Matrix3x3.hpp>
#include <Arithmetic.hpp>

namespace Dawn
{
	Matrix3x3::Matrix3x3( )
	{
		this->Identity( );
	}

	void Matrix3x3::Identity( )
	{
		m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] = 1.0f;

		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] = 0.0f;
	}

	D_BOOL Matrix3x3::IsIdentity( ) const
	{
		if( Dawn::Equal( m_M[ 0 ], 1.0f ) &&
			Dawn::IsZero( m_M[ 1 ] ) &&
			Dawn::IsZero( m_M[ 2 ] ) &&
			Dawn::IsZero( m_M[ 3 ] ) &&
			Dawn::Equal( m_M[ 4 ], 1.0f ) &&
			Dawn::IsZero( m_M[ 5 ] ) &&
			Dawn::IsZero( m_M[ 6 ] ) &&
			Dawn::IsZero( m_M[ 7 ] ) &&
			Dawn::Equal( m_M[ 8 ], 1.0f ) )
		{
			return D_TRUE;
		}

		return D_FALSE;
	}
}
