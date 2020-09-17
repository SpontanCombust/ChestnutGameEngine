#include "engine/engine.hpp"

namespace engine
{
    bool CEngine::InitSDL() 
    {
        bool retcode = true;
        int flags;

        flags = SDL_INIT_EVERYTHING;
        if( SDL_Init( flags ) < 0 )
        {
            LOG( "SDL failed to initialize!" );
            LOG( SDL_GetError() );
            retcode = false;
        }

        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG( "SDL_image failed to initialize!" );
            LOG( IMG_GetError() );
            retcode = false;
        }

        return retcode;
    }
    
    void CEngine::DeinitSDL() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool CEngine::Create( int winWidth, int winHeight )
    {
        bool retcode = true;

        retcode = InitSDL();

        if( retcode )
        {
            m_renderWindow = new graphics::CRenderWindow( m_appTitle.c_str(),
                                                            winWidth,
                                                            winHeight,
                                                            m_windowStartPosX,
                                                            m_windowStartPosY,
                                                            m_windowFlags,
                                                            m_rendererFlags );
            retcode &= (m_renderWindow != nullptr);
            retcode &= OnUserCreate();
        }

        return retcode;
    }

    void CEngine::Start()
    {
        m_wasStarted = true;
        StartInternal();
    }

    bool CEngine::Update()
    {
        return true;
    }

    void CEngine::StartInternal()
    {
        // PLACEHOLDER; TO BE CHANGED LATER
        while( m_isRunning )
        {
            OnUserUpdate();
            Update();

            SDL_Delay(3000);
            m_isRunning = false;
        }
    }

    void CEngine::Close()
    {
        if( m_wasStarted )
        {
            OnUserClose();

            delete m_renderWindow;

            DeinitSDL();
        }
        m_wasStarted = false;
    }

    CEngine::~CEngine()
    {
        if( m_wasStarted )
            Close();
    }

    bool CEngine::OnUserCreate() { return true; }
    bool CEngine::OnUserUpdate() { return true; }
    void CEngine::OnUserClose() {}

} // namespace engine
