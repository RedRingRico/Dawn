#ifndef __DAWN_XBOXVERTEXCACHE_HPP__
#define __DAWN_XBOXVERTEXCACHE_HPP__

#include <xtl.h>
#include <VertexCache.hpp>

namespace Dawn
{
	class XboxVertexCache : public VertexCache
	{
	public:
		XboxVertexCache( );
		virtual ~XboxVertexCache( );

		virtual D_UINT32 Initialise( );

		virtual D_UINT32 Add( const D_MEMSIZE p_VertexCount,
			const D_BYTE *p_pVertices,
			const D_MEMSIZE p_IndexCount,
			const D_UINT16 *p_pIndices,
			const D_UINT32 p_MaterialID );

		virtual void Clear( );

		virtual void FlushLine( const D_MEMSIZE p_Index );

		virtual D_MEMSIZE FlushFullestLine( );

		virtual void Flush( );

		virtual D_UINT64 Attributes( ) const;
		virtual D_MEMSIZE AttributeCount( ) const;
		virtual D_MEMSIZE VertexCapacity( ) const;
		virtual D_MEMSIZE IndexCapacity( ) const;
		virtual D_MEMSIZE LineCount( ) const;
		
	private:
		virtual D_MEMSIZE AttribToSize( const D_BYTE p_Attribute ) const;
	};
}

#endif
