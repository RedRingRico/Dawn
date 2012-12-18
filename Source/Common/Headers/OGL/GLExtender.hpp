#ifndef __DAWN_OGL_GLEXTENDER_HPP__
#define __DAWN_OGL_GLEXTENDER_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <list>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

extern PFNGLBINDVERTEXARRAYPROC __dglBindVertexArray;

///////////////////////////////////////////////////////////////////////////////
// CORE FUNCTIONS /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define dglClear		glClear
#define dglGetString	glGetString

#define dglBindVertexArray	__dglBindVertexArray

#ifdef __cplusplus
}
#endif

namespace Dawn
{
	class GLExtender
	{
	public:
		GLExtender( ){ }
		~GLExtender( ){ }

		D_UINT32 Initialise( );

		D_BOOL IsSupported( const char *p_pExtension,
			const D_BOOL p_WindowingSystem = D_FALSE ) const;

	private:
		std::list< std::string > m_GLExtensions;
		std::list< std::string > m_WindowingSystemExtensions;
	};
}

#endif
