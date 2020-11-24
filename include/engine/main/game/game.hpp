#ifndef __CHESTNUT_GAME_H__
#define __CHESTNUT_GAME_H__

#include "world.hpp"
#include "../app/render_window.hpp"
#include "engine/misc/interval_timer.hpp"

namespace chestnut
{
    class CChestnutGame
    {
    protected:
        CRenderWindow *m_parentRenderWindow;
        CTimer *m_gameTimer;

        bool m_isRunning;
        bool m_isSuspended;

    
    public:
        CChestnutGame( CRenderWindow *renderWindow );

        CChestnutWorld theWorld;

        virtual bool onCreate();
        virtual bool onStart();
        virtual bool onUpdate( float deltaTime );
        virtual bool onSuspend();
        virtual bool onEnd();

        virtual ~CChestnutGame() {}
    };
    
} // namespace chestnut


#endif // __CHESTNUT_GAME_H__