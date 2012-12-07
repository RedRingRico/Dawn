#ifndef __DAWN_VECTOR4_HPP__
#define __DAWN_VECTOR4_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	class Vector4
	{
	public:
		D_EXPLICIT Vector4( )
			{ m_V[ 0 ] = m_V[ 1 ] = m_V[ 2 ] = m_V[ 3 ] = 0.0f; }
		D_EXPLICIT Vector4( const D_FLOAT32 p_X, const D_FLOAT32 p_Y,
			const D_FLOAT32 p_Z, const D_FLOAT32 p_W );
		~Vector4( ){ }

		void Normalise( );

		D_FLOAT32 Magnitude( ) const;
		D_FLOAT32 MagnitudeSq( ) const;

		D_FLOAT32 Dot( ) const;

		void Set( const D_FLOAT32 p_X, const D_FLOAT32 p_Y,
			const D_FLOAT32 p_Z, const D_FLOAT32 p_W );
		void SetX( const D_FLOAT32 p_X );
		void SetY( const D_FLOAT32 p_Y );
		void SetZ( const D_FLOAT32 p_Z );
		void SetW( const D_FLOAT32 p_W );

		D_FLOAT32 GetX( ) const;
		D_FLOAT32 GetY( ) const;
		D_FLOAT32 GetZ( ) const;
		D_FLOAT32 GetW( ) const;

		D_BOOL IsZero( ) const;
		void Zero( );
		void Clean( );

		D_BOOL operator==( const Vector4 &p_Other ) const;
		D_BOOL operator!=( const Vector4 &p_Other ) const;

		Vector4 operator-( ) const;

		Vector4 operator+( const Vector4 &p_Other ) const;
		Vector4 operator-( const Vector4 &p_Other ) const;
		Vector4 operator*( const Vector4 &p_Other ) const;
		Vector4 operator*( const D_FLOAT32 p_Scalar ) const;
		Vector4 operator/( const D_FLOAT32 p_Scalar ) const;

		Vector4 &operator+=( const Vector4 &p_Other );
		Vector4 &operator-=( const Vector4 &p_Other );
		Vector4 &operator*=( const Vector4 &p_Other );
		Vector4 &operator*=( const D_FLOAT32 p_Scalar );
		Vector4 &operator/=( const D_FLOAT32 p_Scalar );

	private:
		D_FLOAT32 m_V[ 4 ];
	};
}

#endif

