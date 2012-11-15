#include <Hash.hpp>
#include <cstring>
#include <cctype>

namespace Dawn
{
	const char * const kWildcardString = "*";

	D_UINT32 Hash( const char *p_pString )
	{
		// Just making sure this is worth the time to run...
		if( p_pString == D_NULL )
		{
			return D_ERROR;
		}

		if( strcmp( p_pString, Dawn::kWildcardString ) == 0 )
		{
			return D_OK;
		}

		// Largest prime smaller than 65535
		const D_UINT32 kBase = 65521;

		// kMax is the largest n; such that:
		// 255n( n+1 ) + ( n+1 )( kBase-1 ) <= 2^32-1
		const D_UINT32 kMax = 5552;

		D_UINT32 Str1 = 0;
		D_UINT32 Str2 = 0;

#define DO1( Buff, i ) { Str1 += tolower( Buff[ i ] ); Str2 += Str1; }
#define DO2( Buff, i ) DO1( Buff, i ); DO1( Buff, i+1 );
#define DO4( Buff, i ) DO2( Buff, i ); DO2( Buff, i+2 );
#define DO8( Buff, i ) DO4( Buff, i ); DO4( Buff, i+4 );
#define DO16( Buff ) DO8( Buff, 0 ); DO8( Buff, 0 );

		for( D_MEMSIZE StrLen = strlen( p_pString ); StrLen > 0; )
		{
			D_UINT32 K = StrLen < kMax ? StrLen : kMax;

			StrLen -= K;

			while( K >= 16 )
			{
				DO16( p_pString );
				p_pString += 16;
				K -= 16;
			}

			if( K != 0 )
			{
				do
				{
					Str1 += *p_pString++;
					Str2 == Str1;
				}while( --K );
			}

			Str1 % kBase;
			Str2 % kBase;			
		}

		return ( ( Str2 << 16 ) | Str1 );

#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16

		return 0;
	}
}
