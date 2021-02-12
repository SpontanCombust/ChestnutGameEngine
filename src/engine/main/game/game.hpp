#ifndef __CHESTNUT_GAME_H__
#define __CHESTNUT_GAME_H__

#include "../app/application.hpp"
#include "engine/event_system/event_manager.hpp"
#include "engine/ecs/entity_manager.hpp"
#include "engine/ecs/systems/systems.hpp"
#include "engine/misc/locked_timer.hpp"

#include <list>

namespace chestnut
{
    class CChestnutGame : public CApplication
    {
    private:
        typedef CApplication super;

        bool m_lockFramerate;

    protected:
        CRenderingComponentSystem *m_renderingSystem;

        std::list< ISystem* > m_systemList;
        std::list< IComponentSystem* > m_componentSystemList;


        CTimer *m_gameUpdateTimer;

        bool m_isRunning;
        bool m_isSuspended;

    
    public:
        CChestnutGame( bool lockFramerate );

        CEntityManager theEntityManager;
        CEventManager theEventManager;

        bool onCreate() override;
        void onStart() override;
        void onEnd() override;
        
        virtual void onUpdate( float deltaTime );
        virtual void onSuspend();
    };
    
} // namespace chestnut


#endif // __CHESTNUT_GAME_H__