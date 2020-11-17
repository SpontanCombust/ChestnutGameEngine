#include "engine/app/application.hpp"

namespace chestnut
{
    CChestnutApplication::CChestnutApplication()
    {
        m_wasStarted = false;
        m_isRunning = false;
        m_renderWindow = nullptr;

        m_appTitle = "App";
        m_windowStartPosX = 0;
        m_windowStartPosY = 0;
        m_windowFlags = SDL_WINDOW_SHOWN;
        m_rendererFlags = SDL_RENDERER_ACCELERATED;
    }

    bool CChestnutApplication::initSDL() 
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
    
    void CChestnutApplication::deinitSDL() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool CChestnutApplication::create( int winWidth, int winHeight )
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

            retcode &= onUserCreate();
        }

        return retcode;
    }

    void CChestnutApplication::start()
    {
        m_wasStarted = true;
        enterGameLoop();
    }

    bool CChestnutApplication::update()
    {
        theWorld.update(1); //TODO delta time
        return true;
    }

    void CChestnutApplication::enterGameLoop()
    {
        m_isRunning = true;
        //TODO PLACEHOLDER; TO BE CHANGED LATER
        while( m_isRunning )
        {
            onUserUpdate();
            update();

            if( SDL_GetTicks() > 5000 )
                m_isRunning = false;
        }
    }

    void CChestnutApplication::close()
    {
        if( m_wasStarted )
        {
            onUserClose();

            delete m_renderWindow;

            deinitSDL();
        }
        m_wasStarted = false;
    }

    CChestnutApplication::~CChestnutApplication()
    {
        close();
    }

    bool CChestnutApplication::onUserCreate() { return true; }
    bool CChestnutApplication::onUserUpdate() { return true; }
    void CChestnutApplication::onUserClose() {}

} // namespace chestnut
