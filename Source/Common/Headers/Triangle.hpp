#ifndef __DAWN_GAMEENTITY_TRIANGLE_HPP__
#define __DAWN_GAMEENTITY_TRIANGLE_HPP__

#include <GameEntity.hpp>
#include <Renderer.hpp>
#include <Shader.hpp>

namespace Dawn
{
	class TriangleEntity : public GameEntity
	{
	public:
		TriangleEntity( const ZED::Renderer::Renderer *p_pRenderer );
		~TriangleEntity( );

		virtual ZED_UINT32 Initialise( );
		virtual void Update( );
		virtual void Render( );

	private:
		ZED::Renderer::Renderer *m_pRenderer;
		ZED::Renderer::Shader *m_pShader;
		ZED_FLOAT32 m_YRotation;
	};
}

#endif

