#pragma once

#include <SDL2/SDL.h>

namespace engine { namespace graphics {

    class CRenderWindow
    {
    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        int m_width;
        int m_height;
    public:
        CRenderWindow() = delete;
        CRenderWindow( const char *title, int width, int height, int x = 0, int y = 0,
                            int windowFlags = 0, int rendererFlags = 0 );
        ~CRenderWindow();
        int getWindowHeight();
        int getWindowWidth();
    };
}}