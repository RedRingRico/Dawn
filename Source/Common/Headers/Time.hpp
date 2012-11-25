#ifndef __DAWN_TIME_HPP__
#define __DAWN_TIME_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	D_BOOL StartTime( );
	// Seconds
	D_FLOAT32 GetTimeS( );
	// Milliseconds
	D_FLOAT32 GetTimeMS( );
	// Microseconds
	D_FLOAT32 GetTimeMiS( );
	// Nanoseconds
	D_FLOAT32 GetTimeNS( );
}

#endif
