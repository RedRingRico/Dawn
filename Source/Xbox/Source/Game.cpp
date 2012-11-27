#include <Game.hpp>
#include <XboxRenderer.hpp>
#include <Time.hpp>

namespace Dawn
{
	Game::Game( )
	{
	}

	Game::~Game( )
	{
		if( m_pRenderer )
		{
			delete m_pRenderer;
			m_pRenderer = D_NULL;
		}
	}

	D_UINT32 Game::Initialise( const D_BOOL p_FullScreen )
	{
		m_pRenderer = new Dawn::XboxRenderer( );

		// Set up the width and height using the A/V pack
		DWORD AVPack = XGetAVPack( );
		DWORD VideoStandard = XGetVideoStandard( );
		DWORD GameRegion = XGetGameRegion( );
		DWORD VideoFlags = XGetVideoFlags( );

		m_Canvas.Width( 640 );
		m_Canvas.Height( 480 );
		m_Canvas.Widescreen( D_FALSE );
		m_Canvas.Interlaced( D_TRUE );
		m_Canvas.PAL60( D_FALSE );

		switch( AVPack )
		{
		case XC_AV_PACK_SCART:
			{
				// Only PAL machines support SCART
				if( VideoStandard != XC_VIDEO_STANDARD_PAL_I ||
					GameRegion != XC_GAME_REGION_RESTOFWORLD )
				{
					return D_FAIL;
				}

				// Is this widescreen and/or PAL-60?
				if( VideoFlags & XC_VIDEO_FLAGS_WIDESCREEN )
				{
					m_Canvas.Widescreen( D_TRUE );
				}

				if( VideoFlags & XC_VIDEO_FLAGS_PAL_60Hz )
				{
					m_Canvas.PAL60( D_TRUE );

					m_Canvas.Width( 640 );
					m_Canvas.Height( 480 );
					break;
				}				

				m_Canvas.Width( 640 );
				m_Canvas.Height( 576 );

				break;
			}
		case XC_AV_PACK_HDTV:
			{
				if( VideoFlags & XC_VIDEO_FLAGS_HDTV_480p )
				{
					m_Canvas.Interlaced( D_FALSE );
					m_Canvas.Width( 720 );
					m_Canvas.Height( 480 );
                    break;
				}
				if( VideoFlags & XC_VIDEO_FLAGS_HDTV_720p )
				{
					m_Canvas.Interlaced( D_FALSE );
					m_Canvas.Width( 1280 );
					m_Canvas.Height( 720 );
					break;
				}
				if( VideoFlags & XC_VIDEO_FLAGS_HDTV_1080i )
				{
					m_Canvas.Interlaced( D_TRUE );
					m_Canvas.Width( 1920 );
					m_Canvas.Height( 1080 );
					break;
				}

				// Something went wrong trying to determine the HD mode
				return D_ERROR;
			}
		case XC_AV_PACK_RFU:
		case XC_AV_PACK_SVIDEO:
		case XC_AV_PACK_STANDARD:
			{
				// Check for PAL or NTSC
				switch( VideoStandard )
				{
				case XC_VIDEO_STANDARD_NTSC_M:
					{
						// Not inside North America?
						if( GameRegion != XC_GAME_REGION_NA )
						{
							return D_ERROR;
						}

						// Widescreen?
						if( VideoFlags & XC_VIDEO_FLAGS_WIDESCREEN )
						{
							m_Canvas.Widescreen( D_TRUE );
						}

						m_Canvas.Width( 640 );
						m_Canvas.Height( 480 );

						break;
					}
				case XC_VIDEO_STANDARD_NTSC_J:
					{
						// Not inside of Japan?
						if( GameRegion != XC_GAME_REGION_JAPAN )
						{
							return D_ERROR;
						}

						// Widescreen?
						if( VideoFlags & XC_VIDEO_FLAGS_WIDESCREEN )
						{
							m_Canvas.Widescreen( D_TRUE );
						}

						m_Canvas.Width( 640 );
						m_Canvas.Height( 480 );

						break;
					}
				case XC_VIDEO_STANDARD_PAL_I:
					{
						// Not outside of Japan or North America?
						if( GameRegion != XC_GAME_REGION_RESTOFWORLD )
						{
							return D_ERROR;
						}

						// Is this Widescreen and/or PAL-60?
                        if( VideoFlags & XC_VIDEO_FLAGS_WIDESCREEN )
						{
							m_Canvas.Widescreen( );
						}

						if( VideoFlags & XC_VIDEO_FLAGS_PAL_60Hz )
						{
							m_Canvas.PAL60( D_TRUE );

							m_Canvas.Width( 640 );
							m_Canvas.Height( 480 );

							break;
						}

						m_Canvas.Width( 640 );
						m_Canvas.Height( 576 );

						break;
					}
				}
				
				break;
			}
		}

		m_Canvas.Colour( FORMAT_ARGB8 );
		m_Canvas.DepthStencil( FORMAT_D24S8 );
		m_Canvas.BackBufferCount( 1 );

		if( m_pRenderer->Create( m_Canvas ) != D_OK )
		{
			return D_ERROR;
		}

		m_pRenderer->SetClearColour( 0.15f, 0.0f, 0.15f );

		Dawn::StartTime( );

		return D_OK;
	}

	void Game::Update( const D_FLOAT64 p_ElapsedGameTime )
	{
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( D_TRUE, D_TRUE, D_TRUE );
		m_pRenderer->EndScene( );
	}

	D_UINT32 Game::Execute( )
	{
		while( 1 )
		{
			this->Update( 0.0f );
			this->Render( );
		}

		return D_OK;
	}
}
