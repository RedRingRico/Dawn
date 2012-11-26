#ifndef __DAWN_MATRIX3X3_HPP__
#define __DAWN_MATRIX3X3_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	// Forward-declarations
	class Vector3;
	class Quaternion;

	// The matix is stored in column-major form:
	// 0 3 6
	// 1 4 7
	// 2 5 8

	class Matrix3x3
	{
	public:
		D_EXPLICIT Matrix3x3( );

		// Set this matrix to the identity matrix
		void Identity( );
		D_BOOL IsIdentity( ) const;
		D_BOOL IsZero( ) const;

		// Any near-zero values are to be zeroed
		void Clean( );

		// Access and manipulate the matrix via vectors [both row and column]
		void SetRows( const Vector3 &p_Row1, const Vector3 &p_Row2,
			const Vector3 &p_Row3 );
		void GetRows( Vector3 &p_Row1, Vector3 &p_Row2,
			Vector3 &p_Row3 ) const;
		Vector3 GetRow( const D_MEMSIZE p_Index ) const;

		void SetColumns( const Vector3 &p_Column1, const Vector3 &p_Column2,
			const Vector3 &p_Column3 );
		void GetColumns( Vector3 &p_Column1, Vector3 &p_Column2,
			Vector3 &p_Column3 ) const;
		void GetColumn( const D_MEMSIZE p_Index ) const;

		// Get the matrix as a contiguous array
		D_INLINE D_FLOAT32 *GetMatrix( ) const
		{
			D_FLOAT32 *pRaw = new D_FLOAT32[ 9 ];

			for( D_MEMSIZE i = 0; i < 9; ++i )
			{
				pRaw[ i ] = m_M[ i ];
			}

			return pRaw;
		}

		// -- ROTATION OPERATIONS -- //
		// Quaternion rotation
		Matrix3x3 &Rotate( const Quaternion &p_Quaternion );
		// Axis-angle rotation
		Matrix3x3 &Rotate( const Vector3 &p_Axis, D_FLOAT32 p_Angle );
		// Euler rotation
		Matrix3x3 &Rotate( const D_FLOAT32 p_Roll, const D_FLOAT32 p_Pitch,
			const D_FLOAT32 p_Yaw );

		// Rotate on an individual axis
		Matrix3x3 &RotateX( );
		Matrix3x3 &RotateY( );
		Matrix3x3 &RotateZ( );

		// -- SCALING OPERATIONS -- //
		// Uniformly scale
		Matrix3x3 &Scale( const Vector3 p_Scale );
		// Scale on a per-axis basis as defined via a Vector3
		Matrix3x3 &Scale( const D_FLOAT32 p_Scale );
		// Scale each axis individually
		Matrix3x3 &ScaleX( const D_FLOAT32 p_Scale );
		Matrix3x3 &ScaleY( const D_FLOAT32 p_Scale );
		Matrix3x3 &ScaleZ( const D_FLOAT32 p_Scale );

		// Get this matrix as its transpose
		Matrix3x3 &Transpose( );
		// Transpose another matrix using this matrix
		void Transpose( Matrix3x3 &p_Transpose ) const;
		// Transpose this matrix by another matrix
		Matrix3x3 &TransposeOf( const Matrix3x3 &p_Transpose );

		// Get this matrix as its inverse
		Matrix3x3 &Inverse( );
		// Put this matrix's inverse into the parameter
		void Inverse( Matrix3x3 &p_Inverse ) const;
		// Use another matrix's transpose for this matrix
		Matrix3x3 &InverseOf( const Matrix3x3 &p_Inverse );

		D_FLOAT32 Determinate( ) const;
		Matrix3x3 Adjoint( ) const;

		// The diagonal summed
		D_FLOAT32 Trace( ) const;

		// Equality
		D_BOOL operator==( const Matrix3x3 &p_Other ) const;
		D_BOOL operator!=( const Matrix3x3 &p_Other ) const;

		Matrix3x3 operator+( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator-( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator*( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator*( const D_FLOAT32 p_Scalar ) const;
		// Column-wise multiplication with a vector
		Vector3 operator*( const Vector3 &p_Vec ) const;

		Matrix3x3 &operator+=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator-=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator*=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator*=( const D_FLOAT32 p_Scalar );

		// Manipulators
		operator D_FLOAT32*( ){ return m_M; }
		D_FLOAT32 &operator( )( const D_MEMSIZE p_Row,
			const D_MEMSIZE p_Column );
		D_FLOAT32 &operator[ ]( const D_MEMSIZE p_Index )
			{ return m_M[ p_Index ]; }

		// Accessors
		operator const D_FLOAT32*( ){ return m_M; }
		D_FLOAT32 operator( )( const D_MEMSIZE p_Row,
			const D_MEMSIZE p_Column ) const;
		D_FLOAT32 operator[ ]( const D_MEMSIZE p_Index ) const
			{ return m_M[ p_Index ]; }

		// Unary negation
		Matrix3x3 operator-( );

	private:
		D_FLOAT32 m_M[ 9 ];
	};
}

#endif
