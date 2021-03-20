#include "application.hpp"

#include "engine/globals.hpp"

namespace chestnut
{
    // global app instance definition
    CApplication *__g_application = nullptr;


    CApplication::CApplication( float renderInterval ) 
    {
        m_windowFlags   = SDL_WINDOW_SHOWN;
        m_rendererFlags = SDL_RENDERER_ACCELERATED;

        m_updateInterval = -1.f;
        m_renderInterval = renderInterval;

        // set this instance as theApp
        __g_application = this;
    }

    CApplication::CApplication( float renderInterval, float updateInterval ) 
    {
        m_windowFlags   = SDL_WINDOW_SHOWN;
        m_rendererFlags = SDL_RENDERER_ACCELERATED;

        m_updateInterval = updateInterval;
        m_renderInterval = renderInterval;

        // set this instance as theApp
        __g_application = this;
    }

    CApplication::CApplication(float renderInterval, float updateInterval, int windowFlags, int rendererFlags) 
    {
        m_windowFlags   = windowFlags;
        m_rendererFlags = rendererFlags;

        m_updateInterval = updateInterval;
        m_renderInterval = renderInterval;

        // set this instance as theApp
        __g_application = this;
    }

    CApplication::~CApplication() 
    {
        if( __g_application == this )
        {
            __g_application = nullptr;
        }
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

        if( !window.create( "Chestnut App", 800, 600, 0, 0, m_windowFlags, m_rendererFlags ) )
        {
            LOG( "Failed to create a window!" );
            deinitSDL();
            return false;
        }
        window.setWindowRendererAsGlobalRenderer();

        engine.init( m_renderInterval, m_updateInterval );

        return true;
    }

    void CApplication::onStart()
    {
        engine.start();
    }

    void CApplication::onEnd()
    {
        deinitSDL();
    }

    void CApplication::setWindowParams( const char *title, int width, int height, int x, int y ) 
    {
        window.setTitle( title );
        window.setSize( width, height );
        window.setPosition( x, y );
    }

} // namespace chestnut
