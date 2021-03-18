#ifndef __CHESTNUT_APPLICATION_H__
#define __CHESTNUT_APPLICATION_H__

#include "window.hpp"
#include "engine.hpp"
#include "engine/debug/debug.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut
{
    class CApplication
    {
    private:
        int m_windowFlags;
        int m_rendererFlags;
        bool m_lockFramerate;

    public:
        CWindow window;
        CEngine engine;

    public:
        CApplication( bool lockFramerate );
        CApplication( bool lockFramerate, int windowFlags, int rendererFlags );

        virtual bool onCreate();
        virtual void onStart();
        virtual void onEnd();

        virtual ~CApplication() {}

    protected:
        void setWindowParams( const char *title, int width, int height, int x, int y );

    private:
        bool initSDL();
        void deinitSDL();
    };

} // namespace chestnut

#endif // __CHESTNUT_APPLICATION_H__