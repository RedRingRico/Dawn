#ifndef __DAWN_OGLES2_GLES2SHADER_HPP__
#define __DAWN_OGLES2_GLES2SHADER_HPP__

#include <Shader.hpp>
#include <OGLES2/GLES2ShaderData.hpp>

namespace Dawn
{
	class GLES2Shader : public Shader
	{
		friend class GLES2ShaderData;
	public:
		GLES2Shader( );
		virtual ~GLES2Shader( );

		virtual D_UINT32 Compile( const char *p_pSource,
			const D_SHADERTYPE p_Type );
		virtual D_UINT32 Load( const char *p_pFileName,
			const D_SHADERTYPE p_Type );

		virtual D_UINT32 Link( const ShaderData &p_pShader );

		virtual D_UINT32 SetConstantData( const void *p_pData,
			const D_SHADERTYPE p_Type );

		virtual D_UINT32 Activate( );
		virtual void Deactivate( );

		virtual D_BOOL Active( );

	private:
		GLuint m_ProgramID;
		GLuint m_VertexID;
		GLuint m_FragmentID;

		D_BOOL m_Linked;
	};
}

#endif

