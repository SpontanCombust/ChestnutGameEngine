#ifndef __CHESTNUT_GAME_H__
#define __CHESTNUT_GAME_H__

#include "world.hpp"
#include "../app/application.hpp"
#include "engine/misc/interval_timer.hpp"

namespace chestnut
{
    class CChestnutGame : public CApplication
    {
    private:
        typedef CApplication super;

        bool m_enableVsync;

    protected:
        CTimer *m_gameTimer;

        bool m_isRunning;
        bool m_isSuspended;

    
    public:
        CChestnutGame( bool enableVsync );

        CChestnutWorld theWorld;

        virtual bool onCreate() override;
        virtual void onStart() override;
        virtual void onUpdate( float deltaTime );
        virtual void onSuspend();
        virtual void onEnd() override;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_GAME_H__