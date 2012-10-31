#ifndef __DAWN_RENDERER_HPP__
#define __DAWN_RENDERER_HPP__

#include <DataTypes.hpp>

#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
#include <Windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#elif PLATFORM_XBOX
#include <xtl.h>
#endif

#include <CanvasDescription.hpp>

namespace Dawn
{
	class Renderer
	{
	public:
		virtual ~Renderer( ){ }

		virtual D_UINT32 Create( const CanvasDescription &p_Canvas ) = 0;
#if ( PLATFORM_WINDOWS_X86_32 || PLATFORM_WINDOWS_X86_64 )
		virtual D_UINT32 Create( const CanvasDescription &p_Canvas,
			const HDC &p_HDC ) = 0;
		virtual D_UINT32 SetHDC( const HDC &p_HDC ) = 0;
#endif

		// Start the rendering process and clear any buffers required
		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil ) = 0;

		// Swap the front and back buffers
		virtual void EndScene( ) = 0;

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue ) = 0;
	};
}

#endif
