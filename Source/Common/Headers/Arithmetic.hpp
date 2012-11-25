#ifndef __DAWN_ARITHMETIC_HPP__
#define __DAWN_ARITHMETIC_HPP__

#include <DataTypes.hpp>
#include <cmath>

namespace Dawn
{
	D_BOOL IsZero( const D_FLOAT32 p_Value )
	{
		return ( fabs( p_Value ) < D_EPSILON );
	}

	D_BOOL Equal( const D_FLOAT32 p_Value1, const D_FLOAT32 p_Value2 )
	{
		return( IsZero( p_Value1 - p_Value2 ) );
	}
}

#endif
