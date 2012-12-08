#ifndef __DAWN_VECTOR3_HPP__
#define __DAWN_VECTOR3_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	// Forward-declarations
	class Matrix3x3;

	class Vector3
	{
	public:
		D_EXPLICIT Vector3( const D_FLOAT32 p_X, const D_FLOAT32 p_Y,
			const D_FLOAT32 p_Z );
		
		void Zero( );
		void Clean( );

		void Normalise( );

		D_FLOAT32 Magnitude( ) const;
		D_FLOAT32 MagnitudeSq( ) const;

		D_FLOAT32 Distance( const Vector3 &p_Other ) const;
		D_FLOAT32 DistanceSq( const Vector3 &p_Other ) const;

		D_FLOAT32 Dot( const Vector3 &p_Other ) const;
		Vector3 Cross( const Vector3 &p_Other ) const;

		D_BOOL operator==( const Vector3 &p_Other ) const;
		D_BOOL operator!=( const Vector3 &p_Other ) const;

		Vector3 operator+( const Vector3 &p_Other ) const;
		Vector3 operator-( const Vector3 &p_Other ) const;
		Vector3 operator*( const Vector3 &p_Other ) const;
		Vector3 operator*( const Matrix3x3 &p_Matrix ) const;
		Vector3 operator*( const D_FLOAT32 p_Scalar ) const;
		
		Vector3 operator/( const D_FLOAT32 p_Scalar ) const;

		Vector3 &operator+=( const Vector3 &p_Other );
		Vector3 &operator-=( const Vector3 &p_Other );
		Vector3 &operator*=( const Vector3 &p_Other );
		Vector3 &operator*=( const D_FLOAT32 p_Scalar );
		Vector3 &operator/=( const D_FLOAT32 p_Scalar );

		// Accessors
		D_FLOAT32 operator[ ]( const D_MEMSIZE p_Index ) const
			{ return m_V[ p_Index ]; }

		// Manipulators
		D_FLOAT32 &operator[ ]( const D_MEMSIZE p_Index )
			{ return m_V[ p_Index ]; }

	private:
		// 0 == X
		// 1 == Y
		// 2 == Z
		D_FLOAT32 m_V[ 3 ];
	};
}

#endif
