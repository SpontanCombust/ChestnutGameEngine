#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "render_window.hpp"
#include "engine/debug/debug.hpp"
#include "engine/ecs/ecs.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CChestnutGameEngine
    {
    protected:
        // To be changed by inherited class
        std::string m_appTitle;
        int m_windowStartPosX;
        int m_windowStartPosY;
        int m_windowFlags;
        int m_rendererFlags;
        //

        CRenderWindow *m_renderWindow;
        CChestnutECS m_ECS;

        bool m_wasStarted;
        bool m_isRunning;

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
