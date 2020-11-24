#include "engine/main/app/application.hpp"

namespace chestnut
{
    CApplication::CApplication()
    {
        m_renderWindow = nullptr;

        m_appTitle = "App";
        m_windowWidth = 600;
        m_windowHeight = 400;
        m_windowPosX = 400;
        m_windowPosY = 200;
        m_windowFlags = SDL_WINDOW_SHOWN;
        m_rendererFlags = SDL_RENDERER_ACCELERATED;
    }

    bool CApplication::initLibraries() 
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
    
    void CApplication::deinitLibraries() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    void CApplication::init()
    {
        if( !initLibraries() )
            LOG( "Failed to load libraries!" );

        m_renderWindow = new CRenderWindow( m_appTitle.c_str(),
                                            m_windowWidth,
                                            m_windowHeight,
                                            m_windowPosX,
                                            m_windowPosY,
                                            m_windowFlags,
                                            m_rendererFlags 
                                            );

        if( !m_renderWindow )
            LOG( "Failed to create a render window!" );
    }

    void CApplication::start()
    {
        
    }

    void CApplication::deinit()
    {
        delete m_renderWindow;
        deinitLibraries();
    }

} // namespace chestnut
