#include "window.hpp"

#include "engine/debug/debug.hpp"
#include "engine/graphics/renderer.hpp"

namespace chestnut
{
    CWindow::CWindow(  ) 
    {
        m_sdlWindow = nullptr;
        m_sdlRenderer = nullptr;
    }

    CWindow::~CWindow() 
    {
        destroy();
    }

    bool CWindow::create( const char *title, int width, int height, int x, int y, int windowFlags, int rendererFlags )
    {
        m_sdlWindow = SDL_CreateWindow( title, x, y, width, height, windowFlags );

        if( !m_sdlWindow )
        {
            LOG( "Failed to create window. Error: " );
            LOG( SDL_GetError() );
            
            return false;
        }

        m_sdlRenderer = SDL_CreateRenderer( m_sdlWindow, -1, rendererFlags );

        if( !m_sdlRenderer )
        {
            LOG( "Failed to create renderer. Error: " );
            LOG( SDL_GetError() );

            SDL_DestroyWindow( m_sdlWindow );
            m_sdlWindow = nullptr;

            return false;
        }

        return true;
    }

    void CWindow::destroy() 
    {
        if( m_sdlRenderer )
        {
            SDL_DestroyRenderer( m_sdlRenderer );
            m_sdlRenderer = nullptr;
        }
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

    vec2i CWindow::getSize() 
    {
        vec2i size;
        SDL_GetWindowSize( m_sdlWindow, &size.x, &size.y );
        return size;
    }

    void CWindow::setPosition( int x, int y ) 
    {
        SDL_SetWindowPosition( m_sdlWindow, x, y );
    }

    vec2i CWindow::getPosition() 
    {
        vec2i pos;
        SDL_GetWindowPosition( m_sdlWindow, &pos.x, &pos.y );
        return pos;
    }


    void CWindow::setWindowRendererAsGlobalRenderer() 
    {
        CRenderer::setSDLRenderer( m_sdlRenderer );
    }

    SDL_Renderer* CWindow::getSDLRenderer() 
    {
        return m_sdlRenderer;
    }

} // namespace chestnut