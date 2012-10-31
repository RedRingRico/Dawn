#ifndef __DAWN_WINDOWSRENDEREROGL1_HPP__
#define __DAWN_WINDOWSRENDEREROGL1_HPP__

#include <Renderer.hpp>


namespace Dawn
{
	class WindowsRendererOGL1 : public Renderer
	{
	public:
		WindowsRendererOGL1( );
		virtual ~WindowsRendererOGL1( );

		virtual D_UINT32 Create( const CanvasDescription &p_Canvas );
		virtual D_UINT32 Create( const CanvasDescription &p_Canvas,
			const HDC &p_HDC );

		virtual D_UINT32 SetHDC( const HDC &p_HDC );

		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil );

		virtual void EndScene( );

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue );

	private:
		PIXELFORMATDESCRIPTOR	m_PixelFormatDesc;
		HGLRC					m_GLRC;
		HDC						m_DC;

		CanvasDescription		m_Canvas;
	};
}

#endif
