#include "engine/app/engine.hpp"

namespace chestnut
{
    bool CChestnutGameEngine::initSDL() 
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
    
    void CChestnutGameEngine::deinitSDL() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool CChestnutGameEngine::create( int winWidth, int winHeight )
    {
        bool retcode = true;

        retcode = initSDL();

        if( retcode )
        {
            m_renderWindow = new CRenderWindow( m_appTitle.c_str(),
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

    void CChestnutGameEngine::start()
    {
        m_wasStarted = true;
        enterGameLoop();
    }

    bool CChestnutGameEngine::update()
    {
        return true;
    }

    void CChestnutGameEngine::enterGameLoop()
    {
        // PLACEHOLDER; TO BE CHANGED LATER
        while( m_isRunning )
        {
            onUserUpdate();
            update();

            SDL_Delay(3000);
            m_isRunning = false;
        }
    }

    void CChestnutGameEngine::close()
    {
        if( m_wasStarted )
        {
            onUserClose();

            delete m_renderWindow;

            deinitSDL();
        }
        m_wasStarted = false;
    }

    CChestnutGameEngine::~CChestnutGameEngine()
    {
        if( m_wasStarted )
            close();
    }

    bool CChestnutGameEngine::onUserCreate() { return true; }
    bool CChestnutGameEngine::onUserUpdate() { return true; }
    void CChestnutGameEngine::onUserClose() {}

} // namespace chestnut
