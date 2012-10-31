#include <WindowsRendererOGL1.hpp>

namespace Dawn
{
	WindowsRendererOGL1::WindowsRendererOGL1( )
	{
		memset( &m_PixelFormatDesc, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
	}

	WindowsRendererOGL1::~WindowsRendererOGL1( )
	{
		wglMakeCurrent( NULL, NULL );

		if( m_GLRC )
		{
			wglDeleteContext( m_GLRC );
		}
	}

	D_UINT32 WindowsRendererOGL1::Create( const CanvasDescription &p_Canvas )
	{
		if( !m_DC )
		{
			return D_ERROR;
		}

		m_Canvas = p_Canvas;

		switch( m_Canvas.Colour( ) )
		{
		case FORMAT_ARGB8:
			{
				m_PixelFormatDesc.cColorBits = 32;
				m_PixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
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
				m_PixelFormatDesc.cDepthBits = 24;
				m_PixelFormatDesc.cStencilBits = 8;
				break;
			}
		default:
			{
				return D_ERROR;
			}
		}

		m_PixelFormatDesc.nSize = sizeof( PIXELFORMATDESCRIPTOR );
		m_PixelFormatDesc.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW |
			PFD_DOUBLEBUFFER | PFD_TYPE_RGBA;
		m_PixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

		D_UINT32 PixelFormat = ChoosePixelFormat( m_DC, &m_PixelFormatDesc );

		if( PixelFormat == 0 )
		{
			return D_ERROR;
		}

		D_BOOL PixelResult = SetPixelFormat( m_DC, PixelFormat,
			&m_PixelFormatDesc );

		if( PixelFormat == D_FALSE ) 
		{
			return D_ERROR;
		}

		m_GLRC = wglCreateContext( m_DC );

		if( wglMakeCurrent( m_DC, m_GLRC ) == D_FALSE )
		{
			return D_ERROR;
		}

		if( !m_GLRC )
		{
			return D_ERROR;
		}

		glViewport( 0, 0, m_Canvas.Width( ), m_Canvas.Height( ) );

		return D_OK;
	}

	D_UINT32 WindowsRendererOGL1::Create( const CanvasDescription &p_Canvas,
		const HDC &p_HDC )
	{
		if( this->SetHDC( p_HDC ) != D_OK )
		{
			return D_ERROR;
		}

		return this->Create( p_Canvas );
	}

	D_UINT32 WindowsRendererOGL1::SetHDC( const HDC &p_HDC )
	{
		if( !p_HDC )
		{
			return D_ERROR;
		}

		m_DC = p_HDC;

		return D_OK;
	}

	D_UINT32 WindowsRendererOGL1::BeginScene( const D_BOOL p_Colour,
		const D_BOOL p_Depth, const D_BOOL p_Stencil )
	{
		DWORD Flags = 0;

		if( p_Colour )
		{
			Flags |= GL_COLOR_BUFFER_BIT;
		}

		if( p_Depth )
		{
			Flags |= GL_DEPTH_BUFFER_BIT;
		}

		if( p_Stencil )
		{
			Flags |= GL_STENCIL_BUFFER_BIT;
		}

		glClear( Flags );

		return D_OK;
	}

	void WindowsRendererOGL1::EndScene( )
	{
		SwapBuffers( m_DC );
	}

	void WindowsRendererOGL1::SetClearColour( const D_FLOAT32 p_Red,
		const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue )
	{
		glClearColor( p_Red, p_Green, p_Blue, 1.0f );
	}

	D_UINT32 WindowsRendererOGL1::ResizeCanvas( const D_UINT32 p_Width,
		const D_UINT32 p_Height )
	{
		if( p_Width == 0 )
		{
			return D_ERROR;
		}
		if( p_Height == 0 )
		{
			return D_ERROR;
		}

		if( p_Width == m_Canvas.Width( ) && p_Height == m_Canvas.Height( ) )
		{
			return D_OK;
		}

		m_Canvas.Width( p_Width );
		m_Canvas.Height( p_Height );

		glViewport( 0, 0, m_Canvas.Width( ), m_Canvas.Height( ) );

		return D_OK;
	}
}
