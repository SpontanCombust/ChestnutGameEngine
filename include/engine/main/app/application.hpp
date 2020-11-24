#ifndef __CHESTNUT_APPLICATION_H__
#define __CHESTNUT_APPLICATION_H__

#include "render_window.hpp"
#include "engine/main/game/world.hpp"
#include "engine/debug/debug.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CApplication
    {
    protected:
        // To be changed by inherited class
        std::string m_appTitle;
        int m_windowPosX;
        int m_windowPosY;
        int m_windowWidth;
        int m_windowHeight;
        int m_windowFlags;
        int m_rendererFlags;
        //

        CRenderWindow *m_renderWindow;

    public:
        CApplication();

        virtual void init();
        virtual void start();
        virtual void deinit();

        virtual ~CApplication() {}

    protected:
        bool initLibraries();
        void deinitLibraries();
    };


#define CHESTNUT_IMPLEMENT_APP( APP ) \
        int main(int argc, char const *argv[])  \
        {                                       \
            APP app;                            \
                                                \
            app.init();                         \
            app.start();                        \
            app.deinit();                       \
                                                \
            return 0;                           \
        }                                       \

} // namespace chestnut

#endif // __CHESTNUT_APPLICATION_H__