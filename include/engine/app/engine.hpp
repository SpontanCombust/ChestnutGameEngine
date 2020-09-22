#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "engine/debug/debug.hpp"
#include "render_window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CChestnutGameEngine
    {
    protected:
        // To be changed by inherited class +++
        std::string m_appTitle = "App";
        int m_windowStartPosX = 0;
        int m_windowStartPosY = 0;
        int m_windowFlags = SDL_WINDOW_SHOWN;
        int m_rendererFlags = SDL_RENDERER_ACCELERATED;
        // ---

        bool m_wasStarted;
        bool m_isRunning;
        CRenderWindow *m_renderWindow;


    public:
        CChestnutGameEngine();

        bool create( int winWidth, int winHeight );
        void start();
        void close();

        virtual bool onUserCreate();
        virtual bool onUserUpdate();
        virtual void onUserClose();
        virtual ~CChestnutGameEngine();

    protected:
        bool initSDL();
        void deinitSDL();
        bool update();
        void enterGameLoop();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_ENGINE_H__