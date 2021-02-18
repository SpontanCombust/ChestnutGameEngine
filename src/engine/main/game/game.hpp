#ifndef __CHESTNUT_GAME_H__
#define __CHESTNUT_GAME_H__

#include "../app/application.hpp"
#include "engine/event_system/event_manager.hpp"
#include "engine/event_system/events/events.hpp"
#include "engine/ecs/components/components.hpp"
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
        CTimer *m_gameUpdateTimer;

        bool m_isRunning;
        bool m_isSuspended;


        CSDLEventDispatchSystem *m_sdlEventDispatchSystem;
        CTimerSystem *m_timerSystem;
        CRenderingSystem *m_renderingSystem;

        std::list< IUpdatableSystem* > m_updatableSystemsList;
        std::list< IComponentFetchingSystem* > m_componentFetchingSystemsList;
        std::list< CEventRaisingSystem* > m_eventRaisingSystemsList;


        CEntityManager m_entityManager;
        CEventManager m_eventManager;


    public:
        CChestnutGame( bool lockFramerate );

        CEntityManager& getEntityManager();
        CEventManager& getEventManager();

        float getGameTimeInSeconds();

        bool onCreate() override;
        void onStart() override;
        void onEnd() override;
        
        virtual void onUpdate( float deltaTime );
        virtual void onSuspend();

        event_function onQuitEvent( const SMiscSDLEvent& event );


    private:
        eventListener_id_t m_quitListenerID;
        void registerQuitEvent();
        void unregisterQuitEvent();
    };
    
} // namespace chestnut


#endif // __CHESTNUT_GAME_H__