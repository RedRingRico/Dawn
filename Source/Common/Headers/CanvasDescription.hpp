#ifndef __DAWN_CANVASDESCRIPTION_HPP__
#define __DAWN_CANVASDESCRIPTION_HPP__

#include <RenderTypes.hpp>
#include <DataTypes.hpp>

namespace Dawn
{
	class CanvasDescription
	{
	public:
		// Manipulators
		D_INLINE void Width( const D_UINT32 p_Width )
			{ m_Width = p_Width; }
		D_INLINE void Height( const D_UINT32 p_Height )
			{ m_Height = p_Height; }
		D_INLINE void BackBufferCount( const D_UINT32 p_BackBufferCount )
			{ m_BackBufferCount = p_BackBufferCount; }
		D_INLINE void Colour( const RENDERFORMAT p_Colour )
			{ m_Colour = p_Colour; }
		D_INLINE void DepthStencil( const RENDERFORMAT p_DepthStencil )
			{ m_DepthStencil = p_DepthStencil; }
#ifdef PLATFORM_XBOX
		D_INLINE void Interlaced( const D_BOOL p_Interlaced )
			{ m_Interlaced = p_Interlaced; }
		D_INLINE void Widescreen( const D_BOOL p_Widescreen )
			{ m_Widescreen = p_Widescreen; }
		D_INLINE void PAL60( const D_BOOL p_PAL60 )
			{ m_PAL60 = p_PAL60; }
#endif

		// Accessors
		D_INLINE D_UINT32 Width( ) const { return m_Width; }
		D_INLINE D_UINT32 Height( ) const { return m_Height; }
		D_UINT32 BackBufferCount( ) const { return m_BackBufferCount; }
		D_INLINE RENDERFORMAT Colour( ) const { return m_Colour; }
		D_INLINE RENDERFORMAT DepthStencil( ) const { return m_DepthStencil; }
#ifdef PLATFORM_XBOX
		D_INLINE D_BOOL Interlaced( ) const { return m_Interlaced; }
		D_INLINE D_BOOL Widescreen( ) const { return m_Widescreen; }
		D_INLINE D_BOOL PAL60( ) const { return m_PAL60; }
#endif

	private:
		D_UINT32		m_Width;
		D_UINT32		m_Height;
		D_UINT32		m_BackBufferCount;
		RENDERFORMAT	m_Colour;
		RENDERFORMAT	m_DepthStencil;

		// Only the Xbox needs an interlaced, widescreen, and PAL-60 formats
#ifdef PLATFORM_XBOX
		D_BOOL			m_Interlaced;
		D_BOOL			m_Widescreen;
		D_BOOL			m_PAL60;
#endif
	};
}

#endif
