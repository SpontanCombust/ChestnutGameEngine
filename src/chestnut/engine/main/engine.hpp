#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/types.hpp"
#include "chestnut/engine/constants.hpp"
#include "chestnut/engine/misc/auto_timer.hpp"
#include "chestnut/engine/ecs_impl/event_manager.hpp"
#include "chestnut/engine/audio/audio_manager.hpp"
#include "chestnut/engine/ecs_impl/system.hpp"
#include "chestnut/engine/ecs_impl/rendering_system.hpp"

#include <chestnut/ecs/entity_world.hpp>

#include <list>

namespace chestnut::engine
{
    class CHESTNUT_API CEngine
    {
    private:
        bool m_isRunning;

        CAutoTimer *m_updateTimer;

        CWindow* m_window;

        ecs::CEntityWorld m_entityWorld;
        CEventManager m_eventManager;
        CAudioManager m_audioManager;



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

        std::list< SLogicSystemNode > m_listLogicSystemNodes;
        std::list< SRenderingSystemNode > m_listRenderingSystemNodes;


    public:
        // updateInterval:
        //      <= 0 unlocked update rate
        //       > 0 update rate locked to specified interval in seconds
        CEngine( CWindow* window, float updateInterval = -1 );
        ~CEngine();


        CWindow& getWindow();

        ecs::CEntityWorld& getEntityWorld();

        CEventManager& getEventManager();

        CAudioManager& getAudioManager();



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


        // Throws an exception if no logic system has been attached
        void start();

        void stop();

    private:
        void gameLoop();
    };
    
} // namespace chestnut::engine


#include "engine.inl"


