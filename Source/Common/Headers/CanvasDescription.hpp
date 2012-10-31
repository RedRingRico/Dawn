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

		// Accessors
		D_INLINE D_UINT32 Width( ) const { return m_Width; }
		D_INLINE D_UINT32 Height( ) const { return m_Height; }
		D_UINT32 BackBufferCount( ) const { return m_BackBufferCount; }
		D_INLINE RENDERFORMAT Colour( ) const { return m_Colour; }
		D_INLINE RENDERFORMAT DepthStencil( ) const { return m_DepthStencil; }

	private:
		D_UINT32		m_Width;
		D_UINT32		m_Height;
		D_UINT32		m_BackBufferCount;
		RENDERFORMAT	m_Colour;
		RENDERFORMAT	m_DepthStencil;
	};
}

#endif
