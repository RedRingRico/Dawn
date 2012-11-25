#ifndef __DAWN_LINUXRENDEREROGL1_HPP__
#define __DAWN_LINUXRENDEREROGL1_HPP__

#include <Renderer.hpp>

namespace Dawn
{
	class LinuxRendererOGL1 : public Renderer
	{
	public:
		LinuxRendererOGL1( );
		virtual ~LinuxRendererOGL1( );

		// This version of Create will not care if the Display and
		// Window are set, if they are, then they will be used to
		// create a new window.  Otherwise, if they are not set,
		// then the GL context will just be set.
		virtual D_UINT32 Create( const CanvasDescription &p_Canvas );

		virtual D_UINT32 Create( const CanvasDescription &p_Canvas,
			 Display **p_ppDisplay, Window *p_pWindow );

		virtual D_UINT32 SetDisplay( const Display *p_pDisplay );
		virtual D_UINT32 SetWindow( const Window p_Window );

		virtual D_UINT32 GetXVisualInfo( const CanvasDescription &p_Canvas,
			Display *p_pDisplay, XVisualInfo **p_ppVisualInfo );

		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil );

		virtual void EndScene( );

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue );

		virtual D_UINT32 ResizeCanvas( const D_UINT32 p_Width,
			const D_UINT32 p_Height );

	private:
		XVisualInfo *m_pVisualInfo;
		Display *m_pDisplay;
		Window m_Window;

		CanvasDescription m_Canvas;
		GLXContext m_GLXContext;
	};
}

#endif
