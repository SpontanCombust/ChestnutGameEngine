#ifndef __CHESTNUT_APPLICATION_H__
#define __CHESTNUT_APPLICATION_H__

#include "render_window.hpp"
#include "engine/debug/debug.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CApplication
    {
    private:
        std::string m_appTitle;
        int m_windowPosX;
        int m_windowPosY;
        int m_windowWidth;
        int m_windowHeight;
        int m_windowFlags;
        int m_rendererFlags;

    protected:
        CWindow *m_appWindow;
        void setWindowParams( std::string title, int x, int y, int w, int h, int sdlWinFlags = SDL_WINDOW_SHOWN, int sdlRendererFlags = SDL_RENDERER_ACCELERATED );

    public:
        CApplication();

        virtual bool onCreate();
        virtual void onStart();
        virtual void onEnd();

        virtual ~CApplication() {}

    protected:
        bool initSDL();
        void deinitSDL();
    };


#define CHESTNUT_IMPLEMENT_APP( APP ) \
        int main(int argc, char const *argv[])  \
        {                                       \
            APP app;                            \
                                                \
            if( app.onCreate() )                \
            {                                   \
                app.onStart();                  \
                app.onEnd();                    \
            }                                   \
                                                \
            return 0;                           \
        }                                       \

} // namespace chestnut

#endif // __CHESTNUT_APPLICATION_H__