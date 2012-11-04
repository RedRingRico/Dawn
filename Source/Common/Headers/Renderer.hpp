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
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <GL/glext.h>
#elif PLATFORM_PANDORA
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2extimg.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
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
#if ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
		virtual D_UINT32 Create( const CanvasDescription &p_Canvas,
			Display **p_ppDisplay, Window *p_pWindow ) = 0;
		virtual D_UINT32 SetDisplay( const Display *p_pDisplay ) = 0;
		virtual D_UINT32 SetWindow( const Window p_Window ) = 0;
		// Before calling Create, GLX needs to set up the Visual for
		// use later, so set it up and return it
		virtual D_UINT32 GetXVisualInfo( const CanvasDescription &p_Canvas,
			Display *p_pDisplay, XVisualInfo **p_ppVisualInfo ) = 0;
#endif

		// Start the rendering process and clear any buffers required
		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil ) = 0;

		// Swap the front and back buffers
		virtual void EndScene( ) = 0;

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue ) = 0;

		// Adjust the rendering surface
		virtual D_UINT32 ResizeCanvas( const D_UINT32 p_Width,
			const D_UINT32 p_Height ) = 0;
	};
}

#endif
