#ifndef __CHESTNUT_ENGINE_H__
#define __CHESTNUT_ENGINE_H__

#include "window.hpp"
#include "../types.hpp"
#include "../constants.hpp"
#include "../misc/auto_timer.hpp"
#include "../ecs_impl/event_manager.hpp"
#include "../ecs_impl/system.hpp"
#include "../ecs_impl/rendering_system.hpp"

#include <chestnut/ecs/entity_world.hpp>

#include <list>
#include <memory> // shared_ptr

namespace chestnut
{
    class CEngine
    {
    private:
        bool m_isRunning;

        CAutoTimer *m_updateTimer;

        std::shared_ptr<CWindow> m_window;

        ecs::CEntityWorld m_entityWorld;
        CEventManager m_eventManager;



        struct SLogicSystemNode
        {
            ISystem *system;
            systempriority_t priority;
        };
        struct SRenderingSystemNode
        {
            IRenderingSystem *system;
            systempriority_t priority;
        };

        ISystem *m_masterSystem;
        std::list< SLogicSystemNode > m_listLogicSystemNodes;
        std::list< SRenderingSystemNode > m_listRenderingSystemNodes;


    public:
        // updateInterval:
        //      <= 0 unlocked update rate
        //       > 0 update rate locked to specified interval in seconds
        CEngine( std::shared_ptr<CWindow> window, float updateInterval = -1 );
        ~CEngine();


        CWindow& getWindow();

        ecs::CEntityWorld& getEntityWorld();

        CEventManager& getEventManager();



        // Attach system acting as the main logic unit in the engine
        // There can only be one master system at a time
        // Master system always gets updated first
        template< typename SystemType, typename ...Args >
        void attachMasterSystem( Args&&... args );

        // System execution is ordered by ascending priority (the bigger the number the later in order system is updated)
        // Doesn't allow system duplicates
        template< typename SystemType, typename ...Args >
        void attachLogicSystem( systempriority_t priority, Args&&... args );

        // System execution is ordered by ascending priority (the bigger the number the later in order system is updated)
        // Doesn't allow system duplicates
        template< typename SystemType, typename ...Args >
        void attachRenderingSystem( systempriority_t priority, Args&&... args );

        template< typename SystemType >
        bool hasSystem() const;

        // If doesn't find the system returns nullptr
        template< typename SystemType >
        SystemType *getSystem() const;

        // If doesn't find the system returns SYSTEM_PRIORITY_INVALID
        template< typename SystemType >
        systempriority_t getSystemPriority() const;

        template< typename SystemType >
        void detachSystem();



        float getGameUpdatesPerSecond();

        double getGameTimeInSeconds();


        // Throws an exception if master system hasn't been attached
        void start();

        void stop();

    private:
        void gameLoop();
    };
    
} // namespace chestnut


#include "engine.tpp"


#endif // __CHESTNUT_ENGINE_H__