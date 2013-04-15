#ifndef __DAWN_TIME_HPP__
#define __DAWN_TIME_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	ZED_BOOL StartTime( );
	// Seconds
	ZED_UINT64 GetTimeS( );
	// Milliseconds
	ZED_UINT64 GetTimeMS( );
	// Microseconds
	ZED_UINT64 GetTimeMiS( );
	// Nanoseconds
	ZED_UINT64 GetTimeNS( );
}

#endif
