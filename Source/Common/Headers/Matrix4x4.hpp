#ifndef __DAWN_MATRIX4X4_HPP__
#define __DAWN_MATRIX4X4_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	// Forward-declarations
	class Vector3;
	class Vector4;
	class Matrix3x3;
	class Quaternion;

	class Matrix4x4
	{
	public:
		D_EXPLICIT Matrix4x4( ){ this->Identity( ); }

		void Identity( );
		D_BOOL IsIdentity( ) const;
		D_BOOL IsZero( ) const;
		D_FLOAT32 Trace( );

		void Clean( );

		void SetRows( const Vector4 &p_Row1, const Vector4 &p_Row2,
			const Vector4 &p_Row3, const Vector4 &p_Row4 );
		void GetRows( Vector4 &p_Row1, Vector4 &p_Row2, Vector4 &p_Row3,
			Vector4 &p_Row4 ) const;
		Vector4 &GetRow( const D_MEMSIZE p_Index ) const;

		void SetColumns( const Vector4 &p_Column1, const Vector4 &p_Column2,
			const Vector4 &p_Column3, const Vector4 &p_Column4 );
		void GetColumns( Vector4 &p_Column1, Vector4 &p_Column2,
			Vector4 &p_Column3, Vector4 &p_Column4 ) const;
		Vector4 &GetColumn( const D_MEMSIZE p_Index ) const;

		void GetMatrix( D_FLOAT32 *p_pArray ) const
		{
			for( D_MEMSIZE i = 0; i < 16; ++i )
			{
				p_pArray[ i ] = m_M[ i ];
			}
		}

		Matrix4x4 &Translate( const Vector4 &p_Translation );
		Vector3 &Transform( const Vector3 &p_Point ) const;

		Matrix4x4 &Rotate( const Matrix3x3 &p_Rotation );
		Matrix4x4 &Rotate( const Quaternion &p_Quaternion );
		Matrix4x4 &Rotate( const D_FLOAT32 p_Roll, const D_FLOAT32 p_Pitch,
			const D_FLOAT32 p_Yaw );
		Matrix4x4 &Rotate( const Vector3 p_Axis, const D_FLOAT32 p_Angle );
		Matrix4x4 &RotateX( const D_FLOAT32 p_X );
		Matrix4x4 &RotateY( const D_FLOAT32 p_Y );
		Matrix4x4 &RotateZ( const D_FLOAT32 p_Z );

		Matrix4x4 &Scale( const Vector3 &p_Scale );
		Matrix4x4 &Scale( const D_FLOAT32 p_Scale );
		Matrix4x4 &ScaleX( const D_FLOAT32 p_X );
		Matrix4x4 &ScaleY( const D_FLOAT32 p_Y );
		Matrix4x4 &ScaleZ( const D_FLOAT32 p_Z );

		Matrix4x4 &Transpose( );
		void Transpose( Matrix4x4 &p_Transpose ) const;
		Matrix4x4 &TransposeOf( const Matrix4x4 &p_Transpose );

		Matrix4x4 &AffineInverse( );
		void AffineInverse( Matrix4x4 &p_AffineInverse ) const;
		Matrix4x4 &AffineInverseOf( const Matrix4x4 &p_AffineInverse );

		D_BOOL operator==( const Matrix4x4 &p_Other ) const;
		D_BOOL operator!=( const Matrix4x4 &p_Other ) const;

		Matrix4x4 operator+( const Matrix4x4 &p_Other ) const;
		Matrix4x4 operator-( const Matrix4x4 &p_Other ) const;
		Matrix4x4 operator-( ) const;
		Matrix4x4 operator*( const Matrix4x4 &p_Other ) const;
		Matrix4x4 operator*( const Vector4 &p_Vec ) const;
		Matrix4x4 operator*( const D_FLOAT32 p_Scalar ) const;
		
		Matrix4x4 &operator+=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator-=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator*=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator*=( const D_FLOAT32 p_Scalar );

		// Manipulators
		D_FLOAT32 &operator( )( const D_MEMSIZE p_Row,
			const D_MEMSIZE p_Column );
		D_FLOAT32 &operator[ ]( const D_MEMSIZE p_Index )
			{ return m_M[ p_Index ]; }
		D_FLOAT32 &operator[ ]( const int p_Index )
			{ return m_M[ p_Index ]; }

		// Accessors
		D_FLOAT32 operator( )( const D_MEMSIZE p_Row,
			const D_MEMSIZE p_Column ) const;
		D_FLOAT32 operator[ ]( const D_MEMSIZE p_Index ) const 
			{ return m_M[ p_Index ]; }
		D_FLOAT32 operator[ ]( const int p_Index ) const
			{ return m_M[ p_Index ]; }

	private:
		D_FLOAT32 m_M[ 16 ];
	};
}

#endif

