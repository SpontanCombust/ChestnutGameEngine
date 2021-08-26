#include "window.hpp"

#include "../debug/debug.hpp"

#include <cassert>

namespace chestnut
{
    SWindowProperties windowPropertiesDefault( int glVersionMajor, int glVersionMinor ) 
    {
        SWindowProperties properties;

        properties.sdlWindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
#ifdef CHESTNUT_DEBUG
        properties.sdlGLContextFlags = SDL_GL_CONTEXT_DEBUG_FLAG;
        properties.sdlGLContextProfileMask = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
#else
        properties.sdlGLContextFlags = 0;
        properties.sdlGLContextProfileMask = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
#endif
        properties.sdlGLContextVersionMajor = glVersionMajor;
        properties.sdlGLContextVersionMinor = glVersionMinor;

        return properties;
    }

    CWindow::CWindow() 
    {
        m_sdlWindow = nullptr;
        m_sdlGLContext = nullptr;

        int flags;

        flags = SDL_INIT_EVERYTHING;
        if( SDL_Init( flags ) < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL failed to initialize!" );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
        }

        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG_CHANNEL( "WINDOW", "SDL_image failed to initialize!" );
            LOG_CHANNEL( "WINDOW", IMG_GetError() );
            SDL_Quit();
        }

        if( TTF_Init() < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL_ttf failed to initialize!" );
            LOG_CHANNEL( "WINDOW", TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
        }
    }

    CWindow::~CWindow() 
    {
        if( m_sdlWindow )
        {
            destroy();
        }
        
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    bool CWindow::create( const SWindowProperties& windowProperties, const std::string& title, int width, int height, int x, int y, bool useVsync )
    {
        // ========= Prepare SDL_GL ========= //

        // window already exists
        if( m_sdlWindow )
        {
            destroy();
        }

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, windowProperties.sdlGLContextVersionMajor );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, windowProperties.sdlGLContextVersionMinor );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, windowProperties.sdlGLContextFlags );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, windowProperties.sdlGLContextProfileMask );



        // ========= Create window and context ========= //

        m_sdlWindow = SDL_CreateWindow( title.c_str(), x, y, width, height, windowProperties.sdlWindowFlags );
        if( !m_sdlWindow )
        {
            LOG_CHANNEL( "WINDOW", "Failed to create window. Error: " );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            return false;
        }

        m_sdlGLContext = SDL_GL_CreateContext( m_sdlWindow );
        if( !m_sdlGLContext )
        {
            LOG_CHANNEL( "WINDOW", "Failed to create OpenGL context for the window. Error: " );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            SDL_DestroyWindow( m_sdlWindow );
            return false;
        }



        // ========= Init OpenGL ========= //

        GLenum err = glewInit();
        if( err != GLEW_OK )
        {
            LOG_CHANNEL( "WINDOW", "Failed to initialize GLEW! Error: " );
            LOG_CHANNEL( "WINDOW", glewGetErrorString( err ) );
            SDL_GL_DeleteContext( m_sdlGLContext );
            SDL_DestroyWindow( m_sdlWindow );
            return false;
        }

        glViewport( 0, 0, width, height );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear( GL_COLOR_BUFFER_BIT );

        toggleVsync( useVsync );


        return true;
    }

    void CWindow::destroy() 
    {
        SDL_GL_DeleteContext( m_sdlGLContext );
        SDL_DestroyWindow( m_sdlWindow );
        m_sdlWindow = nullptr;
    }

    void CWindow::setTitle( const std::string& title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title.c_str() );
    }

    std::string CWindow::getTitle() 
    {
        return std::string( SDL_GetWindowTitle( m_sdlWindow ) );
    }

    void CWindow::setSize( int w, int h ) 
    {
        SDL_SetWindowSize( m_sdlWindow, w, h );
    }

    int CWindow::getWidth() 
    {
        int w;
        SDL_GetWindowSize( m_sdlWindow, &w, NULL );
        return w;
    }

    int CWindow::getHeight() 
    {
        int h;
        SDL_GetWindowSize( m_sdlWindow, NULL, &h );
        return h;
    }

    void CWindow::setPosition( int x, int y ) 
    {
        SDL_SetWindowPosition( m_sdlWindow, x, y );
    }

    int CWindow::getPositionX() 
    {
        int x;
        SDL_GetWindowPosition( m_sdlWindow, &x, NULL );
        return x;
    }

    int CWindow::getPositionY() 
    {
        int y;
        SDL_GetWindowPosition( m_sdlWindow, NULL, &y );
        return y;
    }

    void CWindow::toggleVsync( bool toggle ) 
    {
        if( toggle )
        {
            SDL_GL_SetSwapInterval(1);
        }
        else
        {
            SDL_GL_SetSwapInterval(0);
        }
    }

    void CWindow::clear() 
    {
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void CWindow::flipBuffer() 
    {
        SDL_GL_SwapWindow( m_sdlWindow );
    }

} // namespace chestnut