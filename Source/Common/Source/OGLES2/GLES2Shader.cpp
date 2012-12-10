#include <OGLES2/GLES2Shader.hpp>
#include <OGLES2/GLES2Extender.hpp>

namespace Dawn
{
	GLES2Shader::GLES2Shader( )
	{
		m_Linked = D_FALSE;
	}

	GLES2Shader::~GLES2Shader( )
	{
		dglDeleteShader( m_VertexID );
		dglDeleteShader( m_FragmentID );
		dglDeleteProgram( m_ProgramID );
	}

	D_UINT32 GLES2Shader::Compile( const char *p_pSource,
		const D_SHADERTYPE p_Type )
	{
		switch( p_Type )
		{
			case D_SHADERTYPE_VERTEX:
			{
				m_VertexID = dglCreateShader( GL_VERTEX_SHADER );
				dglShaderSource( m_VertexID, 1, &p_pSource, NULL );
				dglCompileShader( m_VertexID );

				break;
			}
			case D_SHADERTYPE_FRAGMENT:
			{
				m_FragmentID = dglCreateShader( GL_FRAGMENT_SHADER );
				dglShaderSource( m_FragmentID, 1, &p_pSource, NULL );
				dglCompileShader( m_FragmentID );

				break;
			}
			default:
			{
				return D_ERROR;
			}
		}

		return D_OK;
	}

	D_UINT32 GLES2Shader::Load( const char *p_pFileName,
		const D_SHADERTYPE p_Type )
	{
		return D_OK;
	}

	D_UINT32 GLES2Shader::Link( const ShaderData &p_ShaderData )
	{
		m_ProgramID = dglCreateProgram( );

		dglAttachShader( m_ProgramID, m_VertexID );
		dglAttachShader( m_ProgramID, m_FragmentID );

		for( D_MEMSIZE i = 0; i < p_ShaderData.VertexAttributeCount( ); ++i )
		{
			D_VERTEXATTRIBUTE Attr = p_ShaderData.GetVertexAttribute( i );
			dglBindAttribLocation( m_ProgramID, Attr.Location, Attr.pName );
		}

		dglLinkProgram( m_ProgramID );

		m_Linked = D_TRUE;

		return D_OK;
	}

	D_UINT32 GLES2Shader::SetConstantData( const void *p_pData,
		const D_SHADERTYPE p_Type )
	{
		if( m_Linked )
		{
			return D_OK;
		}

		return D_ERROR;
	}

	D_UINT32 GLES2Shader::Activate( )
	{
		if( m_Linked )
		{
			dglUseProgram( m_ProgramID );
			return D_OK;
		}

		return D_ERROR;
	}

	void GLES2Shader::Deactivate( )
	{
	}

	D_BOOL GLES2Shader::Active( )
	{
		return D_TRUE;
	}
}

