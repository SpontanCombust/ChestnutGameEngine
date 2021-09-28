#include "window.hpp"

#include "../debug/debug.hpp"
#include "../init.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace chestnut
{
    namespace internal
    {
        struct SLibraryWindowHandle
        {
            SDL_Window *sdlWindow;
            SDL_GLContext sdlGLContext;

            SLibraryWindowHandle( SDL_Window *window, SDL_GLContext context )
            {
                sdlWindow = window;
                sdlGLContext = context;
            }

            ~SLibraryWindowHandle()
            {
                SDL_DestroyWindow( sdlWindow );
                SDL_GL_DeleteContext( sdlGLContext );
            }
        };

    } // namespace internal





    std::shared_ptr<CWindow> createWindow( const std::string& title, int width, int height, EWindowDisplayMode displayMode, int x, int y, bool showAfterCreating, bool useVsync ) 
    {
        // if any error happens we'll just return default smart pointer with null inside 
        std::shared_ptr<CWindow> ptr;

        if( !chestnutWasInit() )
        {
            LOG_CHANNEL( "WINDOW", "Can't create a window without first initializing the dependency libraries!" );
            LOG_CHANNEL( "WINDOW", "Use chestnutInit() first!" );
            return ptr;
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

        SDL_Window *window = SDL_CreateWindow( title.c_str(), x, y, width, height, windowFlags );
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


        ptr = std::shared_ptr<CWindow>( new CWindow( new internal::SLibraryWindowHandle( window, context ) ) );

        return ptr;
    }






    CWindow::CWindow( internal::SLibraryWindowHandle *handle ) 
    {
        m_libraryWindowHandle = handle;
    }

    CWindow::~CWindow() 
    {
        delete m_libraryWindowHandle;
    }

    void CWindow::setTitle( const std::string& title ) 
    {
        SDL_SetWindowTitle( m_libraryWindowHandle->sdlWindow, title.c_str() );
    }

    std::string CWindow::getTitle() const 
    {
        return std::string( SDL_GetWindowTitle( m_libraryWindowHandle->sdlWindow ) );
    }

    void CWindow::setDisplayMode( EWindowDisplayMode displayMode ) 
    {
        switch( displayMode )
        {
            case EWindowDisplayMode::WINDOWED:
                SDL_SetWindowFullscreen( m_libraryWindowHandle->sdlWindow, 0 );
                SDL_SetWindowBordered( m_libraryWindowHandle->sdlWindow, SDL_TRUE );
                break;
            case EWindowDisplayMode::WINDOWED_BORDLERLESS:
                SDL_SetWindowFullscreen( m_libraryWindowHandle->sdlWindow, 0 );
                SDL_SetWindowBordered( m_libraryWindowHandle->sdlWindow, SDL_FALSE );
                break;
            case EWindowDisplayMode::FULLSCREEN:
                SDL_SetWindowFullscreen( m_libraryWindowHandle->sdlWindow, SDL_WINDOW_FULLSCREEN );
                break;
            default:
                SDL_SetWindowFullscreen( m_libraryWindowHandle->sdlWindow, 0 );
        }
    }

    EWindowDisplayMode CWindow::getDisplayMode() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

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
        SDL_SetWindowResizable( m_libraryWindowHandle->sdlWindow, resizable ? SDL_TRUE : SDL_FALSE );
    }

    bool CWindow::isResizable() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

        return ( flags & SDL_WINDOW_RESIZABLE ) > 0;
    }

    void CWindow::setSize( int w, int h ) 
    {
        SDL_SetWindowSize( m_libraryWindowHandle->sdlWindow, w, h );
        glViewport( 0, 0, w, h );
    }

    int CWindow::getSizeWidth() const
    {
        int w;
        SDL_GetWindowSize( m_libraryWindowHandle->sdlWindow, &w, NULL );
        return w;
    }

    int CWindow::getSizeHeight() const
    {
        int h;
        SDL_GetWindowSize( m_libraryWindowHandle->sdlWindow, NULL, &h );
        return h;
    }

    void CWindow::setPosition( int x, int y ) 
    {
        SDL_SetWindowPosition( m_libraryWindowHandle->sdlWindow, x, y );
    }

    int CWindow::getPositionX() const
    {
        int x;
        SDL_GetWindowPosition( m_libraryWindowHandle->sdlWindow, &x, NULL );
        return x;
    }

    int CWindow::getPositionY() const
    {
        int y;
        SDL_GetWindowPosition( m_libraryWindowHandle->sdlWindow, NULL, &y );
        return y;
    }

    void CWindow::minimize() 
    {
        SDL_MinimizeWindow( m_libraryWindowHandle->sdlWindow );
    }

    bool CWindow::isMinimized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

        return ( flags & SDL_WINDOW_MINIMIZED ) > 0;
    }

    void CWindow::maximize() 
    {
        SDL_MaximizeWindow( m_libraryWindowHandle->sdlWindow );
    }

    bool CWindow::isMaximized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

        return ( flags & SDL_WINDOW_MAXIMIZED ) > 0;
    }

    void CWindow::restore() 
    {
        SDL_RestoreWindow( m_libraryWindowHandle->sdlWindow );
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
        SDL_ShowWindow( m_libraryWindowHandle->sdlWindow );
    }

    bool CWindow::isShown() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

        return ( flags & SDL_WINDOW_SHOWN ) > 0;
    }

    void CWindow::hide() 
    {
        SDL_HideWindow( m_libraryWindowHandle->sdlWindow );
    }

    bool CWindow::isHidden() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_libraryWindowHandle->sdlWindow );

        return ( flags & SDL_WINDOW_HIDDEN ) > 0;
    }

    void CWindow::clear() 
    {
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void CWindow::flipBuffer() 
    {
        SDL_GL_SwapWindow( m_libraryWindowHandle->sdlWindow );
    }

} // namespace chestnut