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
        int flags;

        flags = SDL_INIT_EVERYTHING;
        if( SDL_Init( flags ) < 0 )
        {
            LOG( "SDL failed to initialize!" );
            LOG( SDL_GetError() );
            return false;
        }

        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG( "SDL_image failed to initialize!" );
            LOG( IMG_GetError() );
            return false;
        }

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
#ifdef CHESTNUT_DEBUG
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG );
#else
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
#endif
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

        return true;
    }

    bool CApplication::initGL() 
    {
        GLenum err = glewInit();

        if( err != GLEW_OK )
        {
            LOG( "Failed to initialize GLEW! Error: " );
            LOG( glewGetErrorString( err ) );
            return false;
        }

        if( !GLEW_VERSION_3_3 )
        {
            LOG( "Needed OpenGL version is not supported by this machine!" );
            return false;
        }

        glViewport( 0, 0, window.getWidth(), window.getHeight() );

        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear( GL_COLOR_BUFFER_BIT );

        return true;
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

        if( !window.create( "Chestnut App", 800, 600, 0, 0 ) )
        {
            LOG( "Failed to create a window!" );
            deinitSDL();
            return false;
        }

        if( !initGL() )
        {
            LOG( "Failed to initialize OpenGL!" );
            deinitSDL();
            return false;
        }

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
