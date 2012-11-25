#ifndef __DAWN_RENDERTYPES_HPP__
#define __DAWN_RENDERTYPES_HPP__

#include <DataTypes.hpp>

typedef enum __RENDERFORMAT
{
	// Colour
	FORMAT_RGB565	= 0x00000001,
	FORMAT_ARGB8	= 0x00000002,

	// Depth and Stencil
	FORMAT_D24S8		= 0x00000003,
	FORMAT_D16			= 0x00000004,

	RENDERFORMAT_UNKNOWN = D_ENUM_PAD
}RENDERFORMAT;

#endif
