#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "engine/event_system/event_manager.hpp"
#include "engine/event_system/events/events.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/ecs/entity_manager.hpp"
#include "engine/ecs/systems/systems.hpp"
#include "engine/misc/locked_timer.hpp"

#include <vector>

namespace chestnut
{
    class CEngine
    {
    public:
        CEntityManager entityManager;
        CEventManager eventManager;

    private:
        CTimer *m_gameUpdateTimer;

        bool m_isRunning;
        bool m_isSuspended;

        CSDLEventDispatchSystem *m_sdlEventDispatchSystem;
        CTimerSystem *m_timerSystem;
        CRenderingSystem *m_renderingSystem;

        std::list< ISystem* > m_systemsList;
        std::list< IComponentSystem* > m_componentSystemsList;


    public:
        CEngine();
        ~CEngine();

        float getGameTimeInSeconds();
        
        void init( bool lockFramerate );
        void start();
        void suspend();
        void stop();

        event_function onQuitEvent( const SQuitRequestEvent& event );

    private:
        void update( float deltaTime );
        void destroy();

        listenerid_t m_quitListenerID;
        void registerQuitEvent();
        void unregisterQuitEvent();
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENGINE_H__