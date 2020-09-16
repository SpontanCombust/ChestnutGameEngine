#include "engine/graphics/render_window.hpp"

#include "engine/debug/debug.hpp"

namespace engine { namespace graphics {

    CRenderWindow::CRenderWindow( char *title, int height, int width, int y, int x,
                                Uint32 windowFlags, Uint32 rendererFlags ) 
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

    void CRenderWindow::close() 
    {
        SDL_DestroyRenderer( m_renderer );
        SDL_DestroyWindow( m_window );
    }

    CRenderWindow::~CRenderWindow() 
    {
        close();
    }

    int CRenderWindow::getWindowHeight() 
    {
        return m_height;
    }

    int CRenderWindow::getWindowWidth() 
    {
        return m_width;
    }

}}