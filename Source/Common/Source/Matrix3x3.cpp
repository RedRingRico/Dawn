#include <Matrix3x3.hpp>
#include <Vector3.hpp>
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

	D_BOOL Matrix3x3::IsZero( ) const
	{
		for( D_MEMSIZE i = 0; i < 9; ++i )
		{
			if( Dawn::IsZero( m_M[ i ] == D_FALSE ) )
			{
				return D_FALSE;
			}
		}

		return D_TRUE;
	}

	void Matrix3x3::Clean( )
	{
		for( D_MEMSIZE i = 0; i < 9; ++i )
		{
			if( Dawn::IsZero( m_M[ i ] == D_TRUE ) )
			{
				m_M[ i ] = 0.0f;
			}
		}
	}

	void Matrix3x3::SetRows( const Vector3 &p_Row1, const Vector3 &p_Row2,
		const Vector3 &p_Row3 )
	{
		m_M[ 0 ] = p_Row1[ 0 ];
		m_M[ 3 ] = p_Row1[ 1 ];
		m_M[ 6 ] = p_Row1[ 2 ];

		m_M[ 1 ] = p_Row2[ 0 ];
		m_M[ 4 ] = p_Row2[ 1 ];
		m_M[ 7 ] = p_Row2[ 2 ];

		m_M[ 2 ] = p_Row3[ 0 ];
		m_M[ 5 ] = p_Row3[ 1 ];
		m_M[ 8 ] = p_Row3[ 2 ];
	}

	void Matrix3x3::GetRows( Vector3 &p_Row1, Vector3 &p_Row2,
		Vector3 &p_Row3 ) const
	{
		p_Row1[ 0 ] = m_M[ 0 ];
		p_Row1[ 1 ] = m_M[ 3 ];
		p_Row1[ 2 ] = m_M[ 6 ];

		p_Row2[ 0 ] = m_M[ 1 ];
		p_Row2[ 1 ] = m_M[ 4 ];
		p_Row2[ 2 ] = m_M[ 7 ];

		p_Row3[ 0 ] = m_M[ 2 ];
		p_Row3[ 1 ] = m_M[ 5 ];
		p_Row3[ 2 ] = m_M[ 8 ];
	}

	Vector3 &Matrix3x3::GetRow( const D_MEMSIZE p_Index ) const
	{
		return Vector3( m_M[ ( p_Index*3 ) ],
						m_M[ ( p_Index*3 )+1 ],
						m_M[ ( p_Index*3 )+2 ] );
	}

	void Matrix3x3::SetColumns( const Vector3 &p_Column1,
		const Vector3 &p_Column2, const Vector3 &p_Column3 )
	{
		m_M[ 0 ] = p_Column1[ 0 ];
		m_M[ 1 ] = p_Column1[ 1 ];
		m_M[ 2 ] = p_Column1[ 2 ];

		m_M[ 3 ] = p_Column2[ 0 ];
		m_M[ 4 ] = p_Column2[ 1 ];
		m_M[ 5 ] = p_Column2[ 2 ];

		m_M[ 6 ] = p_Column3[ 0 ];
		m_M[ 7 ] = p_Column3[ 1 ];
		m_M[ 8 ] = p_Column3[ 2 ];
	}

	void Matrix3x3::GetColumns( Vector3 &p_Column1, Vector3 &p_Column2,
		Vector3 &p_Column3 ) const
	{
		p_Column1[ 0 ] = m_M[ 0 ];
		p_Column1[ 1 ] = m_M[ 1 ];
		p_Column1[ 2 ] = m_M[ 2 ];

		p_Column2[ 0 ] = m_M[ 3 ];
		p_Column2[ 1 ] = m_M[ 4 ];
		p_Column2[ 2 ] = m_M[ 5 ];

		p_Column3[ 0 ] = m_M[ 6 ];
		p_Column3[ 1 ] = m_M[ 7 ];
		p_Column3[ 2 ] = m_M[ 8 ];
	}

	Vector3 &Matrix3x3::GetColumn( const D_MEMSIZE p_Index ) const
	{
		return Vector3( m_M[ p_Index ], m_M[ p_Index+1 ], m_M[ p_Index+2 ] );
	}
}
