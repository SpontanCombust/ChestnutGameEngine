#ifndef __CHESTNUT_GAME_H__
#define __CHESTNUT_GAME_H__

#include "../app/application.hpp"
#include "engine/event_system/event_system.hpp"
#include "engine/ecs/entity_manager.hpp"
#include "engine/misc/interval_timer.hpp"

namespace chestnut
{
    class CChestnutGame : public CApplication
    {
    private:
        typedef CApplication super;

        bool m_lockFramerate;

    protected:
        CTimer *m_gameTimer;

        bool m_isRunning;
        bool m_isSuspended;

    
    public:
        CChestnutGame( bool lockFramerate );

        CEntityManager theEntityManager;
        CEventManager theEventManager;

        virtual bool onCreate() override;
        virtual void onStart() override;
        virtual void onUpdate( float deltaTime );
        virtual void onSuspend();
        virtual void onEnd() override;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_GAME_H__