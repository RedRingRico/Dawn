#ifndef __DAWN_DATATYPES_LINUX_X86_64_HPP__
#define __DAWN_DATATYPES_LINUX_X86_64_HPP__

// For [u]int64_t
#include <stdint.h>
// For size_t
#include <linux/types.h>

typedef unsigned char		D_UCHAR8;
typedef signed char			D_CHAR8;
typedef wchar_t				D_CHAR16;
typedef unsigned char		D_UINT8;
typedef signed char			D_INT8;
typedef unsigned short int	D_UINT16;
typedef signed short int	D_INT16;
typedef unsigned int		D_UINT32;
typedef signed int			D_INT32;
typedef uint64_t			D_UINT64;
typedef int64_t				D_INT64;

#define LITTLE_ENDIAN	1
#define BIG_ENDIAN		0

#define D_32BIT	0
#define D_64BIT	1

#endif

