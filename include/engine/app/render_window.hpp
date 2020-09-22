#ifndef __CHESTNUT_RENDER_WINDOW_H__
#define __CHESTNUT_RENDER_WINDOW_H__

#include <SDL2/SDL.h>

namespace chestnut
{
    class CRenderWindow
    {
    private:
        SDL_Window *m_window;
        static SDL_Renderer *sm_renderer;
        int m_width;
        int m_height;

    public:
        CRenderWindow() = delete;
        CRenderWindow( const char *title, int width, int height, int x = 0, int y = 0,
                            int windowFlags = 0, int rendererFlags = 0 );
        ~CRenderWindow();
        int getWindowHeight();
        int getWindowWidth();

        static SDL_Renderer *getSDLRenderer();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDER_WINDOW_H__
