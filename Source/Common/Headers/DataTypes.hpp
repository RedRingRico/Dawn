#ifndef __DAWN_DATATYPES_HPP__
#define __DAWN_DATATYPES_HPP__

#ifdef PLATFORM_WINDOWS_X86_32
#include <DataTypes_Windows_x86_32.hpp>
#elif PLATFORM_WINDOWS_X86_64	
#include <DataTypes_Windows_x86_64.hpp>
#elif PLATFORM_LINUX_X86_32
#include <DataTypes_Linux_x86_32.hpp>
#elif PLATFORM_LINUX_X86_64
#include <DataTypes_Linux_x86_64.hpp>
#elif PLATFORM_PANDORA
#include <DataTypes_Pandora.hpp>
#elif PLATFORM_XBOX
#include <DataTypes_Xbox.hpp>
#endif

#include <Compiler.hpp>

// Extra data types building off of those defined in the platrform-specific
// header files
typedef D_UCHAR8	D_BYTE;
typedef D_UINT32	D_BOOL;

// Standard types unified under the grand unification datatype therom
typedef size_t		D_MEMSIZE;
typedef float		D_FLOAT32;
typedef double		D_FLOAT64;

#define D_TRUE	1
#define D_FALSE	0

// Return codes
const D_UINT32 D_OK		= 0x00000000;
const D_ERROR_GRAPHICS	= 0x00000001;
const D_UINT32 D_ERROR	= 0xFFFFFFFF;
const D_UINT32 D_FAIL	= D_ERROR;

#if ( D_32BIT == 1 )
const D_MEMSIZE D_ENUM_PAD = 0x7FFFFFFF;
#elif ( D_64BIT == 1 )
const D_MEMSIZE D_ENUM_PAD = 0x7FFFFFFFFFFFFFFF;
#endif

const D_UINT32 TIME_INFINITE = 0xFFFFFFFF;
const D_UINT32 IEEE754_INFINITE32 = 0x7F800000;

const D_FLOAT32 D_EPSILON = 1.0e-6f;
const D_FLOAT32 D_HALFEPSILON = 1.0e-3f;

#endif
