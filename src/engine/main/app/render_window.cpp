#include "render_window.hpp"

#include "engine/debug/debug.hpp"
#include "engine/graphics/renderer.hpp"

namespace chestnut
{
    CWindow::CWindow( const char *title, int width, int height, int x, int y,
                                int windowFlags, int rendererFlags ) 
    {
        m_window = SDL_CreateWindow( title, x, y, width, height, windowFlags );

        if( m_window == NULL )
        {
            LOG( "Failed to create window. Error: " );
            LOG( SDL_GetError() );
        }

        m_renderer = SDL_CreateRenderer( m_window, -1, rendererFlags );

        if( m_renderer == NULL )
        {
            LOG( "Failed to create renderer. Error: " );
            LOG( SDL_GetError() );
        }

        m_height = height;
        m_width = width;
    }

    CWindow::~CWindow() 
    {
        SDL_DestroyRenderer( m_renderer );
        SDL_DestroyWindow( m_window );
    }

    int CWindow::getWindowHeight() 
    {
        return m_height;
    }

    int CWindow::getWindowWidth() 
    {
        return m_width;
    }


    void CWindow::setWindowRendererAsGlobalRenderer() 
    {
        CRenderer::setSDLRenderer( m_renderer );
    }

    SDL_Renderer* CWindow::getSDLRenderer() 
    {
        return m_renderer;
    }

} // namespace chestnut