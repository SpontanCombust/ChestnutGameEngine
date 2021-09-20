#include "window.hpp"

#include "../debug/debug.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <cassert>

namespace chestnut
{
    SWindowProperties::SWindowProperties( int glVersionMajor, int glVersionMinor ) 
    {
        sdlWindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
#ifdef CHESTNUT_DEBUG
        sdlGLContextFlags = SDL_GL_CONTEXT_DEBUG_FLAG;
        sdlGLContextProfileMask = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
#else
        sdlGLContextFlags = 0;
        sdlGLContextProfileMask = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
#endif
        sdlGLContextVersionMajor = glVersionMajor;
        sdlGLContextVersionMinor = glVersionMinor;
    }



    std::shared_ptr<CWindow> createWindow( const SWindowProperties& windowProperties, const std::string& title, int width, int height, int x, int y, bool useVsync ) 
    {
        // if any error happens we'll just return default smart pointer with null inside 
        std::shared_ptr<CWindow> ptr;


        // ========= Init SDL2 ========= //

        int flags;

        flags = SDL_INIT_EVERYTHING;
        if( SDL_Init( flags ) < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL failed to initialize!" );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            return ptr;
        }

        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG_CHANNEL( "WINDOW", "SDL_image failed to initialize!" );
            LOG_CHANNEL( "WINDOW", IMG_GetError() );
            SDL_Quit();
            return ptr;
        }

        if( TTF_Init() < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL_ttf failed to initialize!" );
            LOG_CHANNEL( "WINDOW", TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
            return ptr;
        }


        // ========= Prepare SDL_GL ========= //

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, windowProperties.sdlGLContextVersionMajor );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, windowProperties.sdlGLContextVersionMinor );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, windowProperties.sdlGLContextFlags );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, windowProperties.sdlGLContextProfileMask );



        // ========= Create window and context ========= //

        // changing x and/or y if they were left default, that is to be positioned at the center of the screen
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            if( x < 0 )
            {
                x = displayMode.w / 2 - width / 2;
            }
            if( y < 0 )
            {
                y = displayMode.h / 2 - height / 2;
            }
        }


        SDL_Window *window = SDL_CreateWindow( title.c_str(), x, y, width, height, windowProperties.sdlWindowFlags );
        if( !window )
        {
            LOG_CHANNEL( "WINDOW", "Failed to create window. Error: " );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            return ptr;
        }

        SDL_GLContext context = SDL_GL_CreateContext( window );
        if( !context )
        {
            LOG_CHANNEL( "WINDOW", "Failed to create OpenGL context for the window. Error: " );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            SDL_DestroyWindow( window );
            return ptr;
        }


        // ========= Init OpenGL ========= //

        GLenum err = glewInit();
        if( err != GLEW_OK )
        {
            LOG_CHANNEL( "WINDOW", "Failed to initialize GLEW! Error: " );
            LOG_CHANNEL( "WINDOW", glewGetErrorString( err ) );
            SDL_GL_DeleteContext( context );
            SDL_DestroyWindow( window );
            return ptr;
        }

        glViewport( 0, 0, width, height );

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear( GL_COLOR_BUFFER_BIT );

        int interval = useVsync ? 1 : 0;
        SDL_GL_SetSwapInterval( interval );        


        ptr = std::shared_ptr<CWindow>( new CWindow( window, context ) );

        return ptr;
    }

    CWindow::CWindow( SDL_Window *window, SDL_GLContext context ) 
    {
        m_sdlWindow = window;
        m_sdlGLContext = context;
    }

    CWindow::~CWindow() 
    {
        SDL_GL_DeleteContext( m_sdlGLContext );
        SDL_DestroyWindow( m_sdlWindow );

        //! THIS WAY IT DOESN'T SUPPORT MULTIPLE WINDOWS IN SITUATIONS WHEN THEY'RE ALL NOT DESTROYED SIMULTANOUSLY!
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void CWindow::setTitle( const std::string& title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title.c_str() );
    }

    std::string CWindow::getTitle() 
    {
        return std::string( SDL_GetWindowTitle( m_sdlWindow ) );
    }

    void CWindow::setDisplayMode( EWindowDisplayMode displayMode ) 
    {
        switch( displayMode )
        {
            case EWindowDisplayMode::WINDOWED:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
                SDL_SetWindowBordered( m_sdlWindow, SDL_TRUE );
                break;
            case EWindowDisplayMode::WINDOWED_BORDLERLESS:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
                SDL_SetWindowBordered( m_sdlWindow, SDL_FALSE );
                break;
            case EWindowDisplayMode::FULLSCREEN:
                SDL_SetWindowFullscreen( m_sdlWindow, SDL_WINDOW_FULLSCREEN );
                break;
            default:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
        }
    }

    EWindowDisplayMode CWindow::getDisplayMode() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        if( ( flags & SDL_WINDOW_FULLSCREEN ) > 0 )
        {
            return EWindowDisplayMode::FULLSCREEN;
        }
        else if( ( flags & SDL_WINDOW_BORDERLESS ) > 0 )
        {
            return EWindowDisplayMode::WINDOWED_BORDLERLESS;
        }
        else
        {
            return EWindowDisplayMode::WINDOWED;
        }
    }

    void CWindow::setResizable( bool resizable ) 
    {
        SDL_SetWindowResizable( m_sdlWindow, resizable ? SDL_TRUE : SDL_FALSE );
    }

    bool CWindow::isResizable() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_RESIZABLE ) > 0;
    }

    void CWindow::setSize( int w, int h ) 
    {
        SDL_SetWindowSize( m_sdlWindow, w, h );
        glViewport( 0, 0, w, h );
    }

    int CWindow::getSizeWidth() 
    {
        int w;
        SDL_GetWindowSize( m_sdlWindow, &w, NULL );
        return w;
    }

    int CWindow::getSizeHeight() 
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