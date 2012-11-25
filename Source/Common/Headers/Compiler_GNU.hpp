#ifndef __DAWN_COMPILER_GNU_HPP__
#define __DAWN_COMPILER_GNU_HPP__

#define D_GCCVER ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + \
	__GNU_PATCHLEVEL__ )

#define PACKDATA_BEGIN( p_Align )
#define PACKDATA_END( p_Align ) __attribute__( ( __aligned__( p_Align ) ) )

#define D_INLINE		__inline__
#define D_FORCEINLINE	__forceinline__
#define D_EXPLICIT		explicit

// If GCC is 4.6.0 or greater, then enable C++11 features
#if D_GCCVER >= 40600
#define D_NULL nullptr
#else
#define D_NULL NULL
#endif

#endif
