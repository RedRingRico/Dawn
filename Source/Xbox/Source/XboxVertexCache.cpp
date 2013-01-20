#include <XboxVertexCache.hpp>

namespace Dawn
{
	XboxVertexCache::XboxVertexCache( )
	{
	}

	XboxVertexCache::~XboxVertexCache( )
	{
	}

	D_UINT32 XboxVertexCache::Initialise( )
	{
		return D_OK;
	}

	D_UINT32 XboxVertexCache::Add( const D_MEMSIZE p_VertexCount,
		const D_BYTE *p_pVertexCache, const D_MEMSIZE p_IndexCount,
		const D_UINT16 *p_pIndices, const D_UINT32 p_MaterialID )
	{
		return D_OK;
	}

	void XboxVertexCache::Clear( )
	{
	}

	void XboxVertexCache::FlushLine( const D_MEMSIZE p_Index )
	{
	}

	D_MEMSIZE XboxVertexCache::FlushFullestLine( )
	{
		return 0;
	}

	void XboxVertexCache::Flush( )
	{
	}

	D_UINT64 XboxVertexCache::Attributes( ) const
	{
		return 0xFFFFFFFFFFFFFFFF;
	}

	D_MEMSIZE XboxVertexCache::AttributeCount( ) const
	{
		return 0;
	}

	D_MEMSIZE XboxVertexCache::VertexCapacity( ) const
	{
		return 0;
	}

	D_MEMSIZE XboxVertexCache::IndexCapacity( ) const
	{
		return 0;
	}

	D_MEMSIZE XboxVertexCache::LineCount( ) const
	{
		return 0;
	}

	D_MEMSIZE XboxVertexCache::AttribToSize( const D_BYTE p_Attribute ) const
	{
		return 0;
	}
}
