#include <LinuxRendererOGL1.hpp>
#include <stdio.h>
namespace Dawn
{
	LinuxRendererOGL1::LinuxRendererOGL1( )
	{
		m_pVisualInfo = D_NULL;
		m_pDisplay = D_NULL;
		m_GLXContext = D_NULL;
	}

	LinuxRendererOGL1::~LinuxRendererOGL1( )
	{
		if( m_pVisualInfo )
		{
			XFree( m_pVisualInfo );
		}	
		if( m_GLXContext )
		{
			glFlush( );
			glXMakeCurrent( m_pDisplay, None, NULL );
			glXDestroyContext( m_pDisplay, m_GLXContext );
		}
	}

	D_UINT32 LinuxRendererOGL1::Create( const CanvasDescription &p_Canvas )
	{
		m_GLXContext = glXCreateContext( m_pDisplay, m_pVisualInfo, 0, True );
		glXMakeCurrent( m_pDisplay, m_Window, m_GLXContext );

		return D_OK;
	}


	D_UINT32 LinuxRendererOGL1::Create( const CanvasDescription &p_Canvas,
		Display **p_ppDisplay, Window *p_pWindow )
	{
		return D_OK;
	}

	D_UINT32 LinuxRendererOGL1::SetDisplay( const Display *p_pDisplay )
	{
		m_pDisplay = const_cast< Display * >( p_pDisplay );
		return D_OK;
	}

	D_UINT32 LinuxRendererOGL1::SetWindow( const Window p_Window )
	{
		m_Window = p_Window;
		return D_OK;
	}

	D_UINT32 LinuxRendererOGL1::GetXVisualInfo(
		const CanvasDescription &p_Canvas, Display *p_pDisplay,
		XVisualInfo **p_ppVisualInfo )
	{
		if( p_pDisplay == D_NULL )
		{
			return D_ERROR;
		}

		this->SetDisplay( p_pDisplay );

		m_Canvas = p_Canvas;

		D_INT32 Depth = 0, Stencil = 0, A = 0, R = 0, G = 0, B = 0;
		switch( m_Canvas.DepthStencil () )
		{
			case FORMAT_D24S8:
			{
				Depth = 24;
				Stencil = 8;
				break;
			}
			default:
			{
				return D_ERROR;
			}
		}

		switch( m_Canvas.Colour( ) )
		{
			case FORMAT_ARGB8:
			{
				A = R = G = B = 8;
				break;
			}
			default:
			{
				return D_ERROR;
			}
		}

		D_INT32 Attrs[ ] =
		{
			GLX_X_RENDERABLE,	True,
			GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,	GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
			GLX_RED_SIZE,		R,
			GLX_GREEN_SIZE,		G,
			GLX_BLUE_SIZE,		B,
			GLX_ALPHA_SIZE,		A,
			GLX_DEPTH_SIZE,		Depth,
			GLX_STENCIL_SIZE,	Stencil,
			GLX_DOUBLEBUFFER,	( m_Canvas.BackBufferCount( ) > 0 ?
				True : False ),
			None
		};

		D_INT32 Major = 0, Minor = 0;
		// GLX version 1.3 or greater only
		if( !glXQueryVersion( p_pDisplay, &Major, &Minor ) ||
			( ( Major == 1 ) && ( Minor < 3 ) ) || ( Major < 1 ) )
		{
			return D_ERROR;
		}

		D_INT32 FBCount = 0;
		GLXFBConfig *pFBC = glXChooseFBConfig( p_pDisplay,
			DefaultScreen( p_pDisplay ), Attrs, &FBCount );

		if( !pFBC )
		{
			return D_ERROR;
		}

		GLXFBConfig FBC = pFBC[ 0 ];

		XFree( pFBC );

		m_pVisualInfo = glXGetVisualFromFBConfig( p_pDisplay, FBC );

		( *p_ppVisualInfo ) = m_pVisualInfo;

		return D_OK;
	}

	D_UINT32 LinuxRendererOGL1::BeginScene( const D_BOOL p_Colour,
		const D_BOOL p_Depth, const D_BOOL p_Stencil )
	{
		GLbitfield Flags = 0;

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

	void LinuxRendererOGL1::EndScene( )
	{
		glXSwapBuffers( m_pDisplay, m_Window );
	}

	void LinuxRendererOGL1::SetClearColour( const D_FLOAT32 p_Red,
		const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue )
	{
		glClearColor( p_Red, p_Green, p_Blue, 1.0f );
	}

	D_UINT32 LinuxRendererOGL1::ResizeCanvas( const D_UINT32 p_Width,
		const D_UINT32 p_Height )
	{
		return D_OK;
	}
}

