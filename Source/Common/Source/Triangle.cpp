#include <Triangle.hpp>
#include <Debugger.hpp>

#ifdef ZED_PLATFORM_LINUX
#include <OGL/GLShader.hpp>
#elif defined ZED_PLATFORM_WINDOWS
#include <OGL/GLShader.hpp>
#elif defined ZED_PLATFORM_PANDORA
#include <OGLES2/GLES2Shader.hpp>
#elif defined ZED_PLATFORM_XBOX
#include <XboxShader.hpp>
#else
#error Unknown platform
#endif

#include <cstring>
#include <Matrix4x4.hpp>

namespace Dawn
{
	TriangleEntity::TriangleEntity(
		const ZED::Renderer::Renderer *p_pRenderer )
	{
		m_pRenderer = const_cast< ZED::Renderer::Renderer * >( p_pRenderer );

		m_pVertices = ZED_NULL;
		m_pIndices = ZED_NULL;
		m_YRotation = 0.0f;
		m_pShader = ZED_NULL;
		m_pModel = ZED_NULL;
	}

	TriangleEntity::~TriangleEntity( )
	{
		zedTrace( "Deleting TriangleEntity\n" );
		if( m_pShader )
		{
			zedTrace( "Deleting shader\n" );
			delete m_pShader;
			m_pShader = ZED_NULL;
		}

		if( m_pVertices )
		{
			zedTrace( "Deleting vertices\n" );
			delete [ ] m_pVertices;
			m_pVertices = ZED_NULL;
		}

		if( m_pIndices )
		{
			zedTrace( "Deleting indices\n" );
			delete [ ] m_pIndices;
			m_pIndices = ZED_NULL;
		}

		if( m_pModel )
		{
			zedTrace( "Deleting model\n" );
			delete m_pModel;
			m_pModel = ZED_NULL;
		}
		zedTrace( "End\n" );
	}

	ZED_UINT32 TriangleEntity::Initialise( )
	{
		/*m_pVertices = new ZED_FLOAT32[ 18 ];

		m_pVertices[ 0 ] = 1.0f;
		m_pVertices[ 1 ] = 0.0f;
		m_pVertices[ 2 ] = 0.0f;
		m_pVertices[ 3 ] = 0.15f;
		m_pVertices[ 4 ] = 0.0f;
		m_pVertices[ 5 ] = 0.15f;

		m_pVertices[ 6 ] = 0.0f;
		m_pVertices[ 7 ] = 1.0f;
		m_pVertices[ 8 ] = 0.0f;
		m_pVertices[ 9 ] = 0.0f;
		m_pVertices[ 10 ] = 1.0f;
		m_pVertices[ 11 ] = 0.0f;

		m_pVertices[ 12 ] = 1.0f;
		m_pVertices[ 13 ] = 1.0f;
		m_pVertices[ 14 ] = 0.0f;
		m_pVertices[ 15 ] = 0.15f;
		m_pVertices[ 16 ] = 0.0f;
		m_pVertices[ 17 ] = 0.15f;

		m_pIndices = new ZED_UINT16[ 3 ];

		m_pIndices[ 0 ] = 0;
		m_pIndices[ 1 ] = 1;
		m_pIndices[ 2 ] = 2;*/

		ZED_RENDERER_BACKEND RendererBackEnd = m_pRenderer->BackEnd( );

		switch( RendererBackEnd )
		{
			case ZED_RENDERER_BACKEND_OPENGL:
			{
				m_pShader = new ZED::Renderer::GLShader( );
				m_pModel = new ZED::Renderer::GLModel( m_pRenderer );
				break;
			}
			case ZED_RENDERER_BACKEND_OPENGLES2:
			{
				break;
			}
			case ZED_RENDERER_BACKEND_DIRECT3D:
			{
				break;
			}
			case ZED_RENDERER_BACKEND_DIRECT3D_XBOX:
			{
				break;
			}
			default:
			{
				return ZED_GRAPHICS_ERROR;
			}
		}

		const ZED_CHAR8 *VShaderName =
			"../../Data/Linux/Shaders/VertColour.vsh";
		const ZED_CHAR8 *FShaderName =
			"../../Data/Linux/Shaders/VertColour.fsh";

		m_pShader->Compile( &VShaderName, ZED_VERTEX_SHADER, ZED_TRUE );
		m_pShader->Compile( &FShaderName, ZED_FRAGMENT_SHADER, ZED_TRUE );

		ZED_SHADER_VERTEXATTRIBUTE_GL pAttributes[ 2 ];

		pAttributes[ 0 ].Index = 0;
		pAttributes[ 0 ].pName = "vPosition";
		pAttributes[ 1 ].Index = 1;
		pAttributes[ 1 ].pName = "vColour";
		m_pShader->SetVertexAttributeTypes( pAttributes, 2 );

		ZED_SHADER_CONSTANT_MAP Constant;
		Constant.Index = 0;
		Constant.Type = ZED_MAT4X4;
		Constant.pName = "uWVP";

		m_pShader->SetConstantTypes( &Constant, 1 );

		if( m_pModel->Load( "../../Data/Linux/Models/untitled.zed" ) !=
			ZED_OK )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void TriangleEntity::Update( )
	{

	}

	void TriangleEntity::Render( )
	{
		m_pRenderer->SetRenderState( ZED_RENDERSTATE_DEPTH, ZED_ENABLE );
		m_pRenderer->SetClippingPlanes( 1.0f, 100000.0f );
		ZED::Arithmetic::Matrix4x4 RotationMatrix;
		ZED::Arithmetic::Matrix4x4 WorldMatrix;
		ZED::Arithmetic::Matrix4x4 PerspProj;
		ZED::Arithmetic::Matrix4x4 WVP;
		ZED::Arithmetic::Vector3 Position( 0.0f, 0.0f, 10.0f );
		ZED::Arithmetic::Vector3 Look( 0.0f, 0.0f, 0.0f );
		ZED::Arithmetic::Vector3 Up( 0.0f, 1.0f, 0.0f );
		m_pRenderer->SetViewLookAt( Position, Look, Up );
		m_pRenderer->GetWVP( &WorldMatrix );
		m_pRenderer->CalcPerspProjMatrix( 45.0f, 1280.0f/800.0f, &PerspProj );
		RotationMatrix.RotateY( m_YRotation );
		m_YRotation += 0.01f;
		m_pRenderer->SetRenderState( ZED_RENDERSTATE_CULLMODE, ZED_CULLMODE_NONE );

		ZED_FLOAT32 Matrix[ 16 ];
//		WorldMatrix.AsFloat( Matrix );
//		RotationMatrix.AsFloat( Matrix );
//		WVP = WorldMatrix*PerspProj;
		WVP = PerspProj*WorldMatrix*RotationMatrix;
		WVP.AsFloat( Matrix );

		m_pShader->Activate( );
		m_pShader->SetConstantData( 0, Matrix );

		m_pModel->Render( );
	/*	m_pRenderer->Render( 3, ( ZED_BYTE *)m_pVertices, 3, m_pIndices, 0x66,
			0, ZED_TRIANGLE_LIST );*/
	}
}

