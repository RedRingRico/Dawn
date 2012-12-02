#ifndef __DAWN_PANDORARENDERER_HPP__
#define __DAWN_PANDORARENDERER_HPP__

#include <Renderer.hpp>

namespace Dawn
{
	class PandoraRenderer : public Renderer
	{
	public:
		PandoraRenderer( );
		virtual ~PandoraRenderer( );
		
		virtual D_UINT32 Create( const CanvasDescription &p_Canvas );

		virtual D_UINT32 SetDisplay( const Display *p_pDisplay );
		virtual D_UINT32 SetWindow( const Window p_Window );

		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil );
		virtual void EndScene( );

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue );

		virtual D_UINT32 ResizeCanvas( const D_UINT32 p_Width,
			const D_UINT32 p_Height );

	private:
		CanvasDescription m_Canvas;

		Display	*m_pDisplay;
		Window	m_Window;

		EGLDisplay	m_EGLDisplay;
		EGLSurface	m_EGLSurface;
		EGLContext	m_EGLContext;

		GLES2Extender m_GLES2Extender;
	};
}

#endif

