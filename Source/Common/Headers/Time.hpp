#ifndef __DAWN_TIME_HPP__
#define __DAWN_TIME_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	ZED_BOOL StartTime( );
	// Seconds
	ZED_FLOAT32 GetTimeS( );
	// Milliseconds
	ZED_FLOAT32 GetTimeMS( );
	// Microseconds
	ZED_FLOAT32 GetTimeMiS( );
	// Nanoseconds
	ZED_FLOAT32 GetTimeNS( );
}

#endif
