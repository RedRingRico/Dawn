#include <Arithmetic.hpp>
#include <Vector3.hpp>

namespace Dawn
{
	Vector3::Vector3( const D_FLOAT32 p_X, const D_FLOAT32 p_Y,
		const D_FLOAT32 p_Z )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
		m_V[ 2 ] = p_Z;
	}

	void Vector3::Zero( )
	{
		m_V[ 0 ] = m_V[ 1 ] = m_V[ 2 ] = 0.0f;
	}

	void Vector3::Clean( )
	{
		if( Dawn::IsZero( m_V[ 0 ] ) )
		{
			m_V[ 0 ] = 0.0f;
		}

		if( Dawn::IsZero( m_V[ 1 ] ) )
		{
			m_V[ 1 ] = 0.0f;
		}

		if( Dawn::IsZero( m_V[ 2 ] ) )
		{
			m_V[ 2 ] = 0.0f;
		}
	}

	void Vector3::Normalise( )
	{
		D_FLOAT32 Squared = m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] +
			m_V[ 2 ]*m_V[ 2 ];

		if( Dawn::IsZero( Squared ) )
		{
			this->Zero( );
		}
		else
		{
			// Save on multiple divisions
			D_FLOAT32 Factor = 1.0f / sqrt( Squared );
			m_V[ 0 ] *= Factor;
			m_V[ 1 ] *= Factor;
			m_V[ 2 ] *= Factor;
		}
	}

	D_FLOAT32 Vector3::Magnitude( ) const
	{

		return ( sqrt( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] +
			m_V[ 2 ]*m_V[ 2 ] ) );
	}

	D_FLOAT32 Vector3::MagnitudeSq( ) const
	{
		return ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] + m_V[ 2 ]*m_V[ 2 ] );
	}

	D_FLOAT32 Vector3::Distance( const Vector3 &p_Other ) const
	{
		D_FLOAT32 X = m_V[ 0 ] - p_Other.m_V[ 0 ];
		D_FLOAT32 Y = m_V[ 1 ] - p_Other.m_V[ 1 ];
		D_FLOAT32 Z = m_V[ 2 ] - p_Other.m_V[ 2 ];

		return 1.0f/sqrt( X*X + Y*Y + Z*Z );
	}

	D_FLOAT32 Vector3::DistanceSq( const Vector3 &p_Other ) const
	{
		D_FLOAT32 X = m_V[ 0 ] - p_Other.m_V[ 0 ];
		D_FLOAT32 Y = m_V[ 1 ] - p_Other.m_V[ 1 ];
		D_FLOAT32 Z = m_V[ 2 ] - p_Other.m_V[ 2 ];

		return ( X*X + Y*Y + Z*Z );
	}

	D_FLOAT32 Vector3::Dot( const Vector3 &p_Other ) const
	{
		return ( m_V[ 0 ]*p_Other.m_V[ 0 ] + m_V[ 1 ]*p_Other.m_V[ 1 ] +
			m_V[ 2 ]*p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::Cross( const Vector3 &p_Other ) const
	{
		return Vector3(
			( m_V[ 1 ]*p_Other.m_V[ 2 ] )-( m_V[ 2 ]*p_Other.m_V[ 1 ] ),
			( m_V[ 2 ]*p_Other.m_V[ 0 ] )-( m_V[ 0 ]*p_Other.m_V[ 2 ] ),
			( m_V[ 0 ]*p_Other.m_V[ 1 ] )-( m_V[ 1 ]*p_Other.m_V[ 0 ] ) );
	}

	D_BOOL Vector3::operator==( const Vector3 &p_Other ) const
	{
		if( Dawn::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) &&
			Dawn::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) &&
			Dawn::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) )
		{
			return D_TRUE;
		}
		return D_FALSE;
	}

	D_BOOL Vector3::operator!=( const Vector3 &p_Other ) const
	{
		if( ( Dawn::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) == D_FALSE ) ||
			( Dawn::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) == D_FALSE ) ||
			( Dawn::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) == D_FALSE ) )
		{
			return D_TRUE;
		}

		return D_FALSE;
	}

	Vector3 Vector3::operator+( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]+p_Other.m_V[ 0 ], m_V[ 1 ]+p_Other.m_V[ 1 ],
			m_V[ 2 ]+p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator-( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]-p_Other.m_V[ 0 ], m_V[ 1 ]-p_Other.m_V[ 1 ],
			m_V[ 2 ]-p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator*( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]*p_Other.m_V[ 0 ], m_V[ 1 ]*p_Other.m_V[ 1 ],
			m_V[ 2 ]*p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator*( const D_FLOAT32 p_Scalar ) const
	{
		return Vector3( m_V[ 0 ]*p_Scalar, m_V[ 1 ]*p_Scalar,
			m_V[ 2 ]*p_Scalar );
	}

	Vector3 Vector3::operator/( const D_FLOAT32 p_Scalar ) const
	{
		// Make sure the caller isn't dividing by zero!
		if( Dawn::IsZero( p_Scalar ) )
		{
			return Vector3( m_V[ 0 ], m_V[ 1 ], m_V[ 2 ] );
		}

		return Vector3( m_V[ 0 ]/p_Scalar, m_V[ 1 ]/p_Scalar,
			m_V[ 2 ]/p_Scalar );
	}

	Vector3 &Vector3::operator+=( const Vector3 &p_Other )
	{
		m_V[ 0 ] += p_Other.m_V[ 0 ];
		m_V[ 1 ] += p_Other.m_V[ 1 ];
		m_V[ 2 ] += p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator-=( const Vector3 &p_Other )
	{
		m_V[ 0 ] -= p_Other.m_V[ 0 ];
		m_V[ 1 ] -= p_Other.m_V[ 1 ];
		m_V[ 2 ] -= p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator*=( const Vector3 &p_Other )
	{
		m_V[ 0 ] *= p_Other.m_V[ 0 ];
		m_V[ 1 ] *= p_Other.m_V[ 1 ];
		m_V[ 2 ] *= p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator*=( const D_FLOAT32 p_Scalar )
	{
		m_V[ 0 ] *= p_Scalar;
		m_V[ 1 ] *= p_Scalar;
		m_V[ 2 ] *= p_Scalar;

		return *this;
	}

	Vector3 &Vector3::operator/=( const D_FLOAT32 p_Scalar )
	{
		if( Dawn::IsZero( p_Scalar ) )
		{
			return *this;
		}

		m_V[ 0 ] /= p_Scalar;
		m_V[ 1 ] /= p_Scalar;
		m_V[ 2 ] /= p_Scalar;

		return *this;
	}
}
