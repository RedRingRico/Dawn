#ifndef __DAWN_VERTEXCACHE_HPP__
#define __DAWN_VERTEXCACHE_HPP__

#include <DataTypes.hpp>

namespace Dawn
{
	class VertexCache
	{
	public:
		virtual ~VertexCache( ) { }

		// Uses the data from the constructor to initialise the
		// cache lines
		virtual D_UINT32 Initialise( ) = 0;

		// Vertices depend on the material ID to store multiple vertices within
		// one cache line
		virtual D_UINT32 Add( const D_MEMSIZE p_VertexCount,
			const D_BYTE *p_pVertices,
			const D_MEMSIZE p_IndexCount,
			const D_UINT16 *p_pIndices,
			const D_UINT32 p_MaterialID ) = 0;
        
		// Completely clear the cache
		virtual void Clear( ) = 0;

		// Flush (render) the specified line
		virtual void FlushLine( const D_MEMSIZE p_Index ) = 0;

		// Returns the index of the fullest cache line after it is cleared
		virtual D_MEMSIZE FlushFullestLine( ) = 0;

		// Flush the whole cache
		virtual void Flush( ) = 0;

		virtual D_UINT64 Attributes( ) const = 0;
		virtual D_MEMSIZE AttributeCount( ) const = 0;
		virtual D_MEMSIZE VertexCapacity( ) const = 0;
		virtual D_MEMSIZE IndexCapacity( ) const = 0;
		virtual D_MEMSIZE LineCount( ) const = 0;

	private:
		virtual D_MEMSIZE AttribToSize( const D_BYTE p_Attribute ) const = 0;
	};
}

#endif
