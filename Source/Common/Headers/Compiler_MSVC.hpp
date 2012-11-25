#ifndef __DAWN_COMPILER_MSVC_HPP__
#define __DAWN_COMPILER_MSVC_HPP__

#define PACKDATA_BEGIN( p_Align ) __declspec( align( p_Align ) )
#define PACKDATA_END( p_Align )

#define D_INLINE		inline
#define D_FORCE_INLINE	__forceinline

#define D_EXPLICIT	explicit

#if( _MSC_VER >= 1600 )
#define D_NULL nullptr
#define CPPVER_11
#else
#define D_NULL NULL
#define CPPVER_03
#endif

#define D_CC_MSVC

#endif
