#ifndef __CHESTNUT_WINDOW_H__
#define __CHESTNUT_WINDOW_H__

#include "engine/maths/vector2.hpp"

#include <SDL2/SDL.h>

namespace chestnut
{
    class CWindow
    {
    private:
        SDL_Window *m_sdlWindow;
        SDL_Renderer *m_sdlRenderer;

    public:
        CWindow();
        ~CWindow();

        bool create( const char *title, int width = 800, int height = 600, int x = 0, int y = 0,
                            int windowFlags = SDL_WINDOW_SHOWN, int rendererFlags = SDL_RENDERER_ACCELERATED );

        void destroy();

        void setTitle( const char *title );
        const char *getTitle();

        void setSize( int w, int h );
        vec2i getSize();

        void setPosition( int x, int y );
        vec2i getPosition();

        void setWindowRendererAsGlobalRenderer();
        SDL_Renderer *getSDLRenderer();

        //TODO flipBuffer()
    };

} // namespace chestnut

#endif // __CHESTNUT_WINDOW_H__
