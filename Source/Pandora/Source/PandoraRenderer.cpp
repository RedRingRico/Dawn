#include <PandoraRenderer.hpp>

namespace Dawn
{
	PandoraRenderer::PandoraRenderer( )
	{
		m_pDisplay = D_NULL;
	}

	PandoraRenderer::~PandoraRenderer( )
	{
		eglDestroyContext( m_EGLDisplay, m_EGLContext );
		eglDestroySurface( m_EGLDisplay, m_EGLSurface );
		eglTerminate( m_EGLDisplay );
	}

	D_UINT32 PandoraRenderer::Create( const CanvasDescription &p_Canvas )
	{
		if( m_pDisplay == D_NULL )
		{
			return D_ERROR;
		}

		m_Canvas = p_Canvas;
		D_INT32 Depth, Stencil, A, R, G, B;

		switch( m_Canvas.DepthStencil( ) )
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
		
		EGLint Major, Minor;
		m_EGLDisplay = eglGetDisplay( ( EGLNativeDisplayType )m_pDisplay );
		
		if( m_EGLDisplay == EGL_NO_DISPLAY )
		{
			return D_ERROR;
		}

		if( !eglInitialize( m_EGLDisplay, &Major, &Minor ) )
		{
			return D_ERROR;
		}

		EGLint ConfigurationCount = 0;

		eglGetConfigs( m_EGLDisplay, D_NULL, 0, &ConfigurationCount );

		if( ConfigurationCount == 0 )
		{
			return D_ERROR;
		}

		EGLConfig Configs[ ConfigurationCount ];

		EGLint UpdatedConfigurationCount;

		if( eglGetConfigs( m_EGLDisplay, Configs, ConfigurationCount,
			&UpdatedConfigurationCount ) != EGL_TRUE )
		{
			return D_ERROR;
		}

		EGLint AttributeList[ ] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_RED_SIZE,	R,
			EGL_GREEN_SIZE,	G,
			EGL_BLUE_SIZE,	B,
			EGL_ALPHA_SIZE,	A,
			EGL_DEPTH_SIZE,	Depth,
			EGL_STENCIL_SIZE,	Stencil,
			EGL_NONE
		};

		EGLint FinalConfigurationCount;

		if( !eglChooseConfig( m_EGLDisplay, AttributeList, Configs,
			ConfigurationCount, &FinalConfigurationCount ) )
		{
			return D_ERROR;
		}

		if( FinalConfigurationCount == 0 )
		{
			return D_ERROR;
		}

		m_EGLSurface = eglCreateWindowSurface( m_EGLDisplay, Configs[ 0 ],
			m_Window, D_NULL );

		if( m_EGLSurface == EGL_NO_SURFACE )
		{
			return D_ERROR;
		}

		const EGLint AttribList[ ] =
		{
			EGL_CONTEXT_CLIENT_VERSION,	2,
			EGL_NONE
		};

		m_EGLContext = eglCreateContext( m_EGLDisplay, Configs[ 0 ],
			EGL_NO_CONTEXT, AttribList );

		if( m_EGLContext == EGL_NO_CONTEXT )
		{
			return D_ERROR;
		}

		XSync( m_pDisplay, False );

		if( eglMakeCurrent( m_EGLDisplay, m_EGLSurface, m_EGLSurface,
			m_EGLContext ) != EGL_TRUE )
		{
			return D_ERROR;
		}

		glViewport( 0, 0, m_Canvas.Width( ), m_Canvas.Height( ) );

		return D_OK;
	}

	D_UINT32 PandoraRenderer::SetDisplay( const Display *p_pDisplay )
	{
		if( p_pDisplay )
		{
			m_pDisplay = const_cast< Display * >( p_pDisplay );
			return D_OK;
		}
		return D_ERROR;
	}

	D_UINT32 PandoraRenderer::SetWindow( const Window p_Window )
	{
		m_Window = p_Window;
		return D_OK;
	}

	D_UINT32 PandoraRenderer::BeginScene( const D_BOOL p_Colour,
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

	void PandoraRenderer::EndScene( )
	{
		eglSwapBuffers( m_EGLDisplay, m_EGLSurface );
	}

	void PandoraRenderer::SetClearColour( const D_FLOAT32 p_Red,
		const D_FLOAT32 p_Green, const D_FLOAT32 p_Blue )
	{
		glClearColor( p_Red, p_Green, p_Blue, 1.0f );
	}

	D_UINT32 PandoraRenderer::ResizeCanvas( const D_UINT32 p_Width,
		const D_UINT32 p_Height )
	{
		glViewport( 0, 0, p_Width, p_Height );
		return D_OK;
	}
}

