#ifndef __DAWN_XBOXRENDERER_HPP__
#define __DAWN_XBOXRENDERER_HPP__

#include <Renderer.hpp>

namespace Dawn
{
	class XboxRenderer : public Renderer
	{
	public:
		XboxRenderer( );
		~XboxRenderer( );

		virtual D_UINT32 Create( const CanvasDescription &p_Canvas );

		virtual D_UINT32 BeginScene( const D_BOOL p_Colour,
			const D_BOOL p_Depth, const D_BOOL p_Stencil );

		virtual void EndScene( );

		virtual void SetClearColour( const D_FLOAT32 p_Red,
			const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue );

		D_INLINE virtual D_UINT32 ResizeCanvas( const D_UINT32 p_Width,
			const D_UINT32 p_Height ) { return D_OK; }

	private:
		CanvasDescription m_Canvas;

		LPDIRECT3D8				m_pD3D;
		LPDIRECT3DDEVICE8		m_pDevice;
		D3DPRESENT_PARAMETERS	m_PresentParams;
		D3DCOLOR				m_ClearColour;
	};
}

#endif
