#include <Time.hpp>
#include <xtl.h>

namespace Dawn
{
	static D_INT64 TimeStart = 0;
	static D_INT64 TimeFrequency = 0;

	D_BOOL StartTime( )
	{
		if( TimeStart == 0 )
		{
			QueryPerformanceCounter(
				reinterpret_cast< LARGE_INTEGER * >( &TimeStart ) );
			QueryPerformanceFrequency(
				reinterpret_cast< LARGE_INTEGER * >( &TimeFrequency ) );

			return D_TRUE;
		}
		return D_FALSE;
	}

	D_FLOAT32 GetTimeS( )
	{
		D_INT64 Counter = 0;

		QueryPerformanceCounter(
			reinterpret_cast< LARGE_INTEGER * >( &Counter ) );

		return static_cast< D_FLOAT32 >(
			( Counter - TimeStart ) /
				static_cast< D_FLOAT64 >( TimeFrequency ) );
	}

	D_FLOAT32 GetTimeMS( )
	{
		D_INT64 Counter = 0;

		QueryPerformanceCounter(
			reinterpret_cast< LARGE_INTEGER * >( &Counter ) );

		return static_cast< D_FLOAT32 >(
			( Counter - TimeStart ) /
				static_cast< D_FLOAT64 >( TimeFrequency ) ) / 1000.0f;
	}

	D_FLOAT32 GetTimeMiS( )
	{
		D_INT64 Counter = 0;

		QueryPerformanceCounter(
			reinterpret_cast< LARGE_INTEGER * >( &Counter ) );

		return static_cast< D_FLOAT32 >(
			( Counter - TimeStart ) /
				static_cast< D_FLOAT64 >( TimeFrequency ) ) / 1000000.0f;
	}

	D_FLOAT32 GetTimeNS( )
	{
		D_INT64 Counter = 0;

		QueryPerformanceCounter(
			reinterpret_cast< LARGE_INTEGER * >( &Counter ) );

		return static_cast< D_FLOAT32 >(
			( Counter - TimeStart ) /
				static_cast< D_FLOAT64 >( TimeFrequency ) ) / 1000000000.0f;
	}
}
