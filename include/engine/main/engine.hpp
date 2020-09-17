#pragma once

#include "engine/graphics/render_window.hpp"
#include "engine/debug/debug.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace engine
{
    class CEngine // TODO come up with a name for the engine
    {
    protected:
        // To be changed by inherited class +++
        std::string m_appTitle = "App";
        int m_windowStartPosX = 0;
        int m_windowStartPosY = 0;
        int m_windowFlags = SDL_WINDOW_SHOWN;
        int m_rendererFlags = SDL_RENDERER_ACCELERATED;
        // ---

        bool m_wasStarted = false;
        bool m_isRunning;
        graphics::CRenderWindow *m_renderWindow;

    public:
        bool create( int winWidth, int winHeight );
        void start();
        void close();

        virtual bool onUserCreate();
        virtual bool onUserUpdate();
        virtual void onUserClose();
        virtual ~CEngine();
    
    protected:
        bool initSDL();
        void deinitSDL();
        bool update();
        void enterGameLoop();
    };
    
} // namespace engine
