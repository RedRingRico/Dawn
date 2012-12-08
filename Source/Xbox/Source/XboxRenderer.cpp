#include <XboxRenderer.hpp>

namespace Dawn
{
	XboxRenderer::XboxRenderer( )
	{
		ZeroMemory( &m_PresentParams, sizeof( D3DPRESENT_PARAMETERS ) );
		m_ClearColour = D3DCOLOR_COLORVALUE( 0.0f, 1.0f, 0.0f, 1.0f );
	}

	XboxRenderer::~XboxRenderer( )
	{
	}

	D_UINT32 XboxRenderer::Create( const CanvasDescription &p_Canvas )
	{
		m_Canvas = p_Canvas;

		if( D_NULL == ( m_pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
		{
			return D_ERROR;
		}

		switch( m_Canvas.Colour( ) )
		{
		case FORMAT_ARGB8:
			{
				m_PresentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
				break;
			}
		default:
			{
				return D_ERROR;
			}
		}

		switch( m_Canvas.DepthStencil( ) )
		{
		case FORMAT_D24S8:
			{
				m_PresentParams.EnableAutoDepthStencil = TRUE;
				m_PresentParams.AutoDepthStencilFormat = D3DFMT_D24S8;
				break;
			}
		default:
			{
				return D_ERROR;
			}
		}

		DWORD Flags = 0;

		if( m_Canvas.Interlaced( ) == D_TRUE )
		{
			Flags |= D3DPRESENTFLAG_INTERLACED;
		}
		else
		{
			Flags |= D3DPRESENTFLAG_PROGRESSIVE;
		}

		if( m_Canvas.Widescreen( ) == D_TRUE )
		{
			Flags |= D3DPRESENTFLAG_WIDESCREEN;
		}

		if( m_Canvas.PAL60( ) == D_TRUE )
		{
			m_PresentParams.FullScreen_PresentationInterval = 60;
		}
		else
		{
			m_PresentParams.FullScreen_PresentationInterval =
				D3DPRESENT_RATE_DEFAULT;
		}

		m_PresentParams.Flags = Flags;
		m_PresentParams.BackBufferWidth = m_Canvas.Width( );
		m_PresentParams.BackBufferHeight = m_Canvas.Height( );
		m_PresentParams.BackBufferCount = m_Canvas.BackBufferCount( );
		m_PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_PresentParams.FullScreen_PresentationInterval =
			D3DPRESENT_INTERVAL_IMMEDIATE;
		m_PresentParams.Windowed = FALSE;

		if( FAILED( m_pD3D->CreateDevice( 0, D3DDEVTYPE_HAL, NULL,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_PresentParams,
			&m_pDevice ) ) )
		{
			return D_ERROR;
		}

		return D_OK;
	}

	D_UINT32 XboxRenderer::BeginScene( const D_BOOL p_Colour,
		const D_BOOL p_Depth, const D_BOOL p_Stencil )
	{
		DWORD Flags = 0;

		if( p_Colour )
		{
			Flags |= D3DCLEAR_TARGET;
		}

		if( p_Depth )
		{
			Flags |= D3DCLEAR_ZBUFFER;
		}

		if( p_Stencil )
		{
			Flags |= D3DCLEAR_STENCIL;
		}

		m_pDevice->Clear( 0L, D_NULL, Flags, m_ClearColour, 1.0f, 0L );

		return D_OK;
	}

	void XboxRenderer::EndScene( )
	{
		m_pDevice->Swap( D3DSWAP_DEFAULT );
	}

	void XboxRenderer::SetClearColour( const D_FLOAT32 p_Red,
		const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue )
	{
		m_ClearColour = D3DCOLOR_COLORVALUE( p_Red, p_Green, p_Blue, 1.0f );
	}
}
