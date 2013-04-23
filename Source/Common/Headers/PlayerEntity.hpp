#ifndef __DAWN_PLAYERENTITY_HPP__
#define __DAWN_PLAYERENTITY_HPP__

#include <GameEntity.hpp>

namespace Dawn
{
	class PlayerEntity : public GameEntity
	{
	public:
		PlayerEntity( );
		virtual ~PlayerEntity( );

		virtual ZED_UINT32 Initialise( );

		virtual void Update( );

		virtual void Render( );
	private:
	};
}

#endif

