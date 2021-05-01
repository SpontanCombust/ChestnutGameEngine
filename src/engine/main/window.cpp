#include "window.hpp"

#include "engine/debug/debug.hpp"

#define WINDOW_FLAGS_DEFAULT 

namespace chestnut
{
    CWindow::CWindow(  ) 
    {
        m_sdlWindow = nullptr;
    }

    CWindow::~CWindow() 
    {
        destroy();
    }

    bool CWindow::create( const char *title, int width, int height, int x, int y )
    {
        m_sdlWindow = SDL_CreateWindow( title, x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

        if( !m_sdlWindow )
        {
            LOG( "Failed to create window. Error: " );
            LOG( SDL_GetError() );
            return false;
        }

        SDL_GLContext context = SDL_GL_CreateContext( m_sdlWindow );
        if( !context )
        {
            LOG( "Failed to create OpenGL context for the window. Error: " );
            LOG( SDL_GetError() );
            SDL_DestroyWindow( m_sdlWindow );
            return false;
        }

        SDL_GL_SetSwapInterval(0);

        return true;
    }

    void CWindow::destroy() 
    {
        if( m_sdlWindow )
        {
            SDL_DestroyWindow( m_sdlWindow );
            m_sdlWindow = nullptr;
        }
    }

    void CWindow::setTitle( const char *title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title );
    }

    const char* CWindow::getTitle() 
    {
        return SDL_GetWindowTitle( m_sdlWindow );
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

    void CWindow::clear() 
    {
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void CWindow::flipBuffer() 
    {
        SDL_GL_SwapWindow( m_sdlWindow );
    }

} // namespace chestnut