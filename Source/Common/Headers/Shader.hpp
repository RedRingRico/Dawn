#ifndef __DAWN_SHADER_HPP__
#define __DAWN_SHADER_HPP__

#if ( PLATFORM_WINDOWS_X86_32 || PLATOFORM_WINDOWS_X86_64 )
#include <OGL/GLShaderDefines.hpp>
#elif ( PLATFORM_LINUX_X86_32 || PLATFORM_LINUX_X86_64 )
#include <OGL/GLShaderDefines.hpp>
#elif ( PLATFORM_PANDORA )
#include <OGLES2/GLES2ShaderDefines.hpp>
#elif ( PLATFORM_XBOX )
#include <D3D/D3DShaderDefines.hpp>
#endif

namespace Dawn
{
	class Shader
	{
	public:
		virtual ~Shader( ){ }

		
	};
}

#endif

