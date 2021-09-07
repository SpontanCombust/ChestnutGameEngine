#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "../event_system/event_manager.hpp"
#include "../event_system/events/events.hpp"
#include "../ecs/components/components.hpp"
#include "../ecs/systems/systems.hpp"
#include "../misc/timers/auto_timer.hpp"
#include "../misc/timers/locked_auto_timer.hpp"
#include "../resources/resource_manager.hpp"

#include <chestnut/ecs/entity_world.hpp>

#include <list>

namespace chestnut
{
    class CEngine
    {
    public:
        ecs::CEntityWorld entityWorld;
        CEventManager eventManager;


    private:
        bool m_wasInit;

        CAutoTimer *m_logicUpdateTimer;
        CAutoTimer *m_renderTimer;

        bool m_isRunning;
        bool m_isSuspended;

        CSDLEventDispatchSystem *m_sdlEventDispatchSystem;
        CTimerSystem *m_timerSystem;
        CKinematicsSystem *m_kinematicsSystem;
        CRenderingSystem *m_renderingSystem;

        std::list< ISystem* > m_systemsList;
        std::list< IComponentSystem* > m_componentSystemsList;


    public:
        CEngine();
        ~CEngine();

        float getGameUpdatesPerSecond();
        float getGameTimeInSeconds();
        
        /**
         * @brief Initlialize engine's timers and systems.
         * 
         * @details
         * It is highly recommended to limit rendering rate as when rendering more frequently than
         * display refresh is simply pointless, especially if the render rate is orders of magnitude
         * higher than display refresh rate.
         * 
         * @param renderInterval interval of rendering to the screen in seconds (-1 for unlocked rate)
         * @param updateInterval interval of updating systems in seconds (-1 for unlocked rate)
         */
        void init( float renderInterval = 1.f / 60.f, float updateInterval = -1 );
        void start();
        void suspend();
        void stop();

        event_function onQuitEvent( const SQuitRequestEvent& event );

    private:
        void gameLoop();
        void update( uint32_t deltaTime );
        void destroy();

        listenerid_t m_quitListenerID;
        void registerQuitEvent();
        void unregisterQuitEvent();
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENGINE_H__