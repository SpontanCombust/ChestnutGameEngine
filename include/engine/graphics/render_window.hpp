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
        CRenderWindow( char *title, int height, int width, int y = 0, int x = 0,
                            Uint32 windowFlags = 0, Uint32 rendererFlags = 0 );
        void close();
        ~CRenderWindow();
        int getWindowHeight();
        int getWindowWidth();
    };
}}