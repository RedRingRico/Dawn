#ifndef __DAWN_DATATYPES_WINDOWS_X86_32_HPP__
#define __DAWN_DATATYPES_WINDOWS_X86_32_HPP__

#include <wchar.h>

typedef unsigned char		D_UCHAR8;
typedef signed char			D_CHAR8;
typedef unsigned char		D_UINT8;
typedef signed char			D_INT8;
typedef unsigned short int	D_UINT16;
typedef signed short int	D_INT16;
typedef unsigned int		D_UINT32;
typedef signed int			D_INT32;
typedef unsigned __int64	D_UINT64;
typedef __int64				D_INT64;
typedef wchar_t				D_CHAR16;

#define LITTLE_ENDIAN	1
#define BIG_ENDIAN		0

#define D_32BIT	1
#define D_64BIT	0

#endif
