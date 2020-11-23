#include "engine/main/app/render_window.hpp"

#include "engine/debug/debug.hpp"
#include "engine/graphics/renderer.hpp"

namespace chestnut
{
    CRenderWindow::CRenderWindow( const char *title, int width, int height, int x, int y,
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

        CRenderer::setSDLRenderer( m_renderer );

        m_height = height;
        m_width = width;
    }

    CRenderWindow::~CRenderWindow() 
    {
        SDL_DestroyRenderer( m_renderer );
        SDL_DestroyWindow( m_window );
    }

    int CRenderWindow::getWindowHeight() 
    {
        return m_height;
    }

    int CRenderWindow::getWindowWidth() 
    {
        return m_width;
    }

} // namespace chestnut