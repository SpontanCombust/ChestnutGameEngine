#include "window.hpp"

#include "../debug/log.hpp"
#include "../init.hpp"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

namespace chestnut::engine
{
    CWindow::CWindow( const char *title, int width, int height, EWindowDisplayMode displayMode, int x, int y, bool showAfterCreating, bool useVsync ) 
    {
        m_sdlWindow = nullptr;
        m_sdlGLContext = nullptr;
        m_framebuffer = nullptr;


        if( !chestnutWasInit() )
        {
            LOG_ERROR( "Can't create a window without first initializing the dependency libraries! Use chestnutInit() first!" );
            return;
        }



        // ========= Create window and context ========= //

        // if x and/or y are lesser than 0 se the position at the center of the screen
        Uint32 windowFlags = SDL_WINDOW_OPENGL;
        if( !showAfterCreating )
        {
            windowFlags |= SDL_WINDOW_HIDDEN;
        }
        if( displayMode == EWindowDisplayMode::WINDOWED_BORDLERLESS )
        {
            windowFlags |= SDL_WINDOW_BORDERLESS;
        }
        else if( displayMode == EWindowDisplayMode::FULLSCREEN )
        {
            windowFlags |= SDL_WINDOW_FULLSCREEN;
        }


        x = ( x < 0 ) ? SDL_WINDOWPOS_CENTERED : x;
        y = ( y < 0 ) ? SDL_WINDOWPOS_CENTERED : y;

        SDL_Window *window = SDL_CreateWindow( title, x, y, width, height, windowFlags );
        if( !window )
        {
            LOG_ERROR( "Failed to create window. Error: " << SDL_GetError() );
            return;
        }

        SDL_GLContext context = SDL_GL_CreateContext( window );
        if( !context )
        {
            LOG_ERROR( "Failed to create OpenGL context for the window. Error: " << SDL_GetError() );
            SDL_DestroyWindow( window );
            return;
        }



        // ========= Init OpenGL ========= //

        GLenum err = glewInit();
        if( err != GLEW_OK )
        {
            LOG_ERROR( "Failed to initialize GLEW! Error: " << (const char *)glewGetErrorString( err ) );
            SDL_GL_DeleteContext( context );
            SDL_DestroyWindow( window );
            return;
        }

        glViewport( 0, 0, width, height );

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //TODO GL config on init with features to be enabled
        glEnable( GL_DEPTH_TEST );

        int interval = useVsync ? 1 : 0;
        SDL_GL_SetSwapInterval( interval );        



        m_sdlWindow = window;
        m_sdlGLContext = context;

        m_framebuffer = new CFramebuffer( width, height );
        m_framebuffer->setClearColor( vec4f{ 0.f, 0.f, 0.f, 1.f } );
    }

    CWindow::~CWindow() 
    {
        SDL_GL_DeleteContext( m_sdlGLContext );
        SDL_DestroyWindow( m_sdlWindow );
        delete m_framebuffer;
    }

    bool CWindow::isValid() const
    {
        if( m_sdlWindow && m_sdlGLContext && m_framebuffer )
        {
            return true;
        }

        return false;
    }

    void CWindow::setTitle( const std::string& title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title.c_str() );
    }

    void CWindow::setTitle( const char *title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title );
    }

    const char *CWindow::getTitle() const 
    {
        return SDL_GetWindowTitle( m_sdlWindow );
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
        *m_framebuffer = std::move( CFramebuffer( w, h ) );
    }

    int CWindow::getSizeWidth() const
    {
        // might as well use framebuffer as it has the same size
        return m_framebuffer->getWidth();
    }

    int CWindow::getSizeHeight() const
    {
        return m_framebuffer->getHeight();
    }

    void CWindow::setPosition( int x, int y ) 
    {
        SDL_SetWindowPosition( m_sdlWindow, x, y );
    }

    int CWindow::getPositionX() const
    {
        int x;
        SDL_GetWindowPosition( m_sdlWindow, &x, NULL );
        return x;
    }

    int CWindow::getPositionY() const
    {
        int y;
        SDL_GetWindowPosition( m_sdlWindow, NULL, &y );
        return y;
    }

    void CWindow::minimize() 
    {
        SDL_MinimizeWindow( m_sdlWindow );
    }

    bool CWindow::isMinimized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_MINIMIZED ) > 0;
    }

    void CWindow::maximize() 
    {
        SDL_MaximizeWindow( m_sdlWindow );
    }

    bool CWindow::isMaximized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_MAXIMIZED ) > 0;
    }

    void CWindow::restore() 
    {
        SDL_RestoreWindow( m_sdlWindow );
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

    void CWindow::show() 
    {
        SDL_ShowWindow( m_sdlWindow );
    }

    bool CWindow::isShown() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_SHOWN ) > 0;
    }

    void CWindow::hide() 
    {
        SDL_HideWindow( m_sdlWindow );
    }

    bool CWindow::isHidden() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_HIDDEN ) > 0;
    }

    const CFramebuffer& CWindow::getFramebuffer() const
    {
        return *m_framebuffer;
    }

    void CWindow::clear() 
    {
        m_framebuffer->bind();
        m_framebuffer->clear();
    }

    void CWindow::flipBuffer() 
    {
        SDL_GL_SwapWindow( m_sdlWindow );
    }

} // namespace chestnut::engine