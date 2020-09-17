#include "engine/main/engine.hpp"

namespace engine
{
    bool CEngine::initSDL() 
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
    
    void CEngine::deinitSDL() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool CEngine::create( int winWidth, int winHeight )
    {
        bool retcode = true;

        retcode = initSDL();

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
            retcode &= onUserCreate();
        }

        return retcode;
    }

    void CEngine::start()
    {
        m_wasStarted = true;
        enterGameLoop();
    }

    bool CEngine::update()
    {
        return true;
    }

    void CEngine::close()
    {
        if( m_wasStarted )
        {
            onUserClose();

            delete m_renderWindow;

            deinitSDL();
        }
        m_wasStarted = false;
    }

    CEngine::~CEngine()
    {
        if( m_wasStarted )
            close();
    }

    bool CEngine::onUserCreate() { return true; }
    bool CEngine::onUserUpdate() { return true; }
    void CEngine::onUserClose() {}

} // namespace engine
