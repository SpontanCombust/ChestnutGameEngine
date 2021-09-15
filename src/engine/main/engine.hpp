#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "window.hpp"
#include "../misc/timers/auto_timer.hpp"
#include "../ecs/event_manager.hpp"

#include <chestnut/ecs/entity_world.hpp>

#include <list>

namespace chestnut
{
    // forward declare because systems take engine as constructor argument
    class ISystem;

    class CEngine
    {
    private:
        bool m_wasInit;
        bool m_isRunning;
        bool m_isSuspended;

        CAutoTimer *m_updateTimer;

        CWindow& m_window;

        ecs::CEntityWorld m_entityWorld;
        CEventManager m_eventManager;

        std::list< ISystem * > m_systemsList;


    public:
        CEngine( CWindow& window );
        ~CEngine();

        CWindow& getWindow();
        ecs::CEntityWorld& getEntityWorld();
        CEventManager& getEventManager();

        float getGameUpdatesPerSecond();
        float getGameTimeInSeconds();
        
        // <= 0 unlocked update rate
        // >  0 update rate locked to specified interval in seconds
        void init( float updateInterval = -1 );
        void start();
        void suspend();
        void stop();

    private:
        void gameLoop();
        void destroy();

        std::shared_ptr< IEventListener > m_quitEventListener;
        void registerQuitEvent();
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENGINE_H__