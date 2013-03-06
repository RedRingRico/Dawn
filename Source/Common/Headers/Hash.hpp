#ifndef __DAWN_HASH_HPP__
#define __DAWN_HASH_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	extern const char * const kWildcardString;

	// Algorithm from Mike McShaffry's Game Coding Complete, Second Edition
	ZED_UINT32 Hash( const char *p_pString );
}

#endif
