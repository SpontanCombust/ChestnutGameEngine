#include "engine/main/app/application.hpp"

namespace chestnut
{
    CApplication::CApplication()
    {
        m_appWindow = nullptr;

        m_appTitle = "App";
        m_windowWidth = 600;
        m_windowHeight = 400;
        m_windowPosX = 400;
        m_windowPosY = 200;
        m_windowFlags = SDL_WINDOW_SHOWN;
        m_rendererFlags = SDL_RENDERER_ACCELERATED;
    }

    void CApplication::setWindowParams( std::string title, int x, int y, int w, int h, int sdlWinFlags, int sdlRendererFlags ) 
    {
        m_appTitle = title;
        m_windowPosX = x;
        m_windowPosY = y;
        m_windowWidth = w;
        m_windowHeight = h;
        m_windowFlags = sdlWinFlags;
        m_rendererFlags = sdlRendererFlags;
    }

    bool CApplication::initSDL() 
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
    
    void CApplication::deinitSDL() 
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool CApplication::onCreate()
    {
        if( !initSDL() )
        {
            LOG( "Failed to load libraries!" );
            return false;
        }

        m_appWindow = new CWindow( m_appTitle.c_str(),
                                            m_windowWidth,
                                            m_windowHeight,
                                            m_windowPosX,
                                            m_windowPosY,
                                            m_windowFlags,
                                            m_rendererFlags 
                                            );

        if( !m_appWindow )
            LOG( "Failed to create a window!" );

        m_appWindow->setWindowRendererAsGlobalRenderer();
        return true;
    }

    void CApplication::onStart()
    {
        
    }

    void CApplication::onEnd()
    {
        delete m_appWindow;
        deinitSDL();
    }

} // namespace chestnut
