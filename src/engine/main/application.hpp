#ifndef __CHESTNUT_APPLICATION_H__
#define __CHESTNUT_APPLICATION_H__

#include "../libs.hpp"
#include "window.hpp"
#include "engine.hpp"
#include "../debug/debug.hpp"

#include <string>

namespace chestnut
{
    class CApplication
    {
    private:
        static CApplication *m_instance;

        float m_updateInterval;
        float m_renderInterval;

    public:
        CWindow window;
        CEngine engine;

    public:
        // -1 for unlocked render rate (not recommended)
        CApplication( float renderInterval );
        // -1 for unlocked render rate (not recommended) and update rate
        CApplication( float renderInterval, float updateInterval );

        virtual bool onCreate();
        virtual void onStart();
        virtual void onEnd();

        static void setInstance( CApplication *app );
        static CApplication *getInstance();

        virtual ~CApplication();

    protected:
        void setWindowParams( const char *title, int width, int height, int x, int y );
    };

} // namespace chestnut

#endif // __CHESTNUT_APPLICATION_H__