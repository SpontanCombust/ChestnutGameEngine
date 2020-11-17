#ifndef __CHESTNUT_APPLICATION_H__
#define __CHESTNUT_APPLICATION_H__

#include "render_window.hpp"
#include "world.hpp"
#include "engine/debug/debug.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CChestnutApplication
    {
    protected:
        // To be changed by inherited class
        std::string m_appTitle;
        int m_windowStartPosX;
        int m_windowStartPosY;
        int m_windowFlags;
        int m_rendererFlags;
        //

        bool m_wasStarted;
        bool m_isRunning;

        CRenderWindow *m_renderWindow;

        CChestnutWorld theWorld;

    public:
        CChestnutApplication();

        bool create( int winWidth, int winHeight );
        void start();
        void close();

        virtual bool onUserCreate();
        virtual bool onUserUpdate();
        virtual void onUserClose();
        virtual ~CChestnutApplication();

    protected:
        bool initSDL();
        void deinitSDL();
        bool update();
        void enterGameLoop();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_APPLICATION_H__