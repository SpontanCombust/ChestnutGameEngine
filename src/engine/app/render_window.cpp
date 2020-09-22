#include "engine/app/render_window.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    SDL_Renderer* CRenderWindow::sm_renderer = nullptr;

    CRenderWindow::CRenderWindow( const char *title, int width, int height, int x, int y,
                                int windowFlags, int rendererFlags ) 
    {
        m_window = SDL_CreateWindow( title, x, y, width, height, windowFlags );

        if( m_window == NULL )
        {
            LOG( "Failed to create window. Error: " );
            LOG( SDL_GetError() );
        }

        sm_renderer = SDL_CreateRenderer( m_window, -1, rendererFlags );

        if( sm_renderer == NULL )
        {
            LOG( "Failed to create renderer. Error: " );
            LOG( SDL_GetError() );
        }

        m_height = height;
        m_width = width;
    }

    CRenderWindow::~CRenderWindow() 
    {
        SDL_DestroyRenderer( sm_renderer );
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

    SDL_Renderer* CRenderWindow::getSDLRenderer() 
    {
        return sm_renderer;
    }

} // namespace chestnut