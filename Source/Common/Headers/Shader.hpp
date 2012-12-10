#ifndef __DAWN_SHADER_HPP__
#define __DAWN_SHADER_HPP__

#if ( PLATFORM_WINDOWS_X86_32 || PLATOFORM_WINDOWS_X86_64 )
#include <OGL/GLShaderData.hpp>
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
#include <OGL/GLShaderData.hpp>
#elif ( PLATFORM_PANDORA )
#include <OGLES2/GLES2ShaderData.hpp>
#elif ( PLATFORM_XBOX )
#include <D3D/D3DShaderData.hpp>
#endif

namespace Dawn
{
	class Shader
	{
	public:
		virtual ~Shader( ){ }

		virtual D_UINT32 Compile( const char *p_pSource,
			const D_SHADERTYPE p_Type ) = 0;
		virtual D_UINT32 Load( const char *p_pFileName,
			const D_SHADERTYPE p_Type ) = 0;

		virtual D_UINT32 Link( const ShaderData &p_pShader ) = 0;

		virtual D_UINT32 SetConstantData( const void *p_pData,
			const D_SHADERTYPE p_Type ) = 0;

		virtual D_UINT32 Activate( ) = 0;
		virtual	void Deactivate( ) = 0;

		virtual D_BOOL Active( ) = 0;
	};
}

#endif

