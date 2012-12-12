#ifndef __DAWN_GLES2EXTENDER_HPP__
#define __DAWN_GLES2EXTENDER_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <list>
#include <string>

// Helper macro for determining the offset to use in the buffer objects
#define D_BUFFER_OFFSET( p_Offset )( ( GLubyte * )NULL + ( p_Offset ) )

#ifdef __cplusplus
extern "C"
{
#endif

typedef void ( GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC )( GLsizei, GLuint * );
typedef void ( GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC )( GLuint );
typedef GLboolean ( GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC )( GLuint );
typedef void ( GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC )( GLsizei n,
	const GLuint * );

#if !defined( GL_OES_vertex_array_object )
#define GL_VERTEX_ARRAY_BINDING_OES	0x85B5
#endif

extern PFNGLGENVERTEXARRAYSOESPROC		__dglGenVertexArrays;
extern PFNGLBINDVERTEXARRAYOESPROC		__dglBindVertexArray;
extern PFNGLISVERTEXARRAYOESPROC		__dglIsVertexArray;
extern PFNGLDELETEVERTEXARRAYSOESPROC	__dglDeleteVertexArrays;

///////////////////////////////////////////////////////////////////////////////
// CORE GLES2 FUNCTIONS ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define dglAttachShader				glAttachShader
#define dglBindAttribLocation		glBindAttribLocation
#define dglBindBuffer				glBindBuffer
#define dglBufferData				glBufferData
#define dglBufferSubData			glBufferSubData
#define dglClear					glClear
#define dglClearColor				glClearColor
#define dglCompileShader			glCompileShader
#define dglCreateProgram			glCreateProgram
#define dglCreateShader				glCreateShader
#define dglDeleteBuffers			glDeleteBuffers
#define dglDeleteProgram			glDeleteProgram
#define dglDeleteShader				glDeleteShader
#define dglDrawElements				glDrawElements
#define dglEnableVertexAttribArray	glEnableVertexAttribArray
#define dglGenBuffers				glGenBuffers
#define dglGetError					glGetError
#define dglGetProgramiv				glGetProgramiv
#define dglGetProgramInfoLog		glGetProgramInfoLog
#define dglGetShaderiv				glGetShaderiv
#define dglGetShaderInfoLog			glGetShaderInfoLog
#define dglGetString				glGetString
#define dglGetUniformLocation		glGetUniformLocation
#define dglLinkProgram				glLinkProgram
#define dglShaderSource				glShaderSource
#define dglUniformMatrix4fv			glUniformMatrix4fv
#define dglUseProgram				glUseProgram
#define dglVertexAttribPointer		glVertexAttribPointer
#define dglViewport					glViewport

///////////////////////////////////////////////////////////////////////////////
// VERTEX ARRAY OBJECTS ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define dglGenVertexArrays		__dglGenVertexArrays
#define dglBindVertexArray		__dglBindVertexArray
#define dglIsVertexArray		__dglIsVertexArray
#define dglDeleteVertexArrays	__dglDeleteVertexArrays


#ifdef __cplusplus
}
#endif

namespace Dawn
{
	class GLES2Extender
	{
	public:
		GLES2Extender( ){ }
		~GLES2Extender( ){ }

		D_UINT32 Initialise( );

		// Check if the extension is supported, using p_EGL
		// to use the EGL extensions list or the GLES2 list
		D_BOOL IsSupported( const char *p_pExtension,
			const D_BOOL p_EGL = D_FALSE );

	private:
		std::list< std::string > m_GLES2Extensions;
		std::list< std::string > m_EGLExtensions;
	};
}

#endif

