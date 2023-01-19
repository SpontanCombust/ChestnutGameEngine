#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/types.hpp"
#include "chestnut/engine/constants.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/resources/resource_manager.hpp"
#include "chestnut/engine/ecs_impl/event_manager.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"
#include "chestnut/engine/ecs_impl/rendering_system.hpp"
#include "chestnut/engine/misc/auto_timer.hpp"
#include "chestnut/engine/audio/audio_manager.hpp"

#include <chestnut/ecs/entity_world.hpp>

#include <list>

namespace chestnut::engine
{
    class CHESTNUT_API CEngine
    {
    private:
        static CEngine *sm_instance;


        bool m_isRunning;

        CAutoTimer *m_updateTimer;

        CWindow& m_window;

        ecs::CEntityWorld m_entityWorld;
        CEventManager m_eventManager;
        CAudioManager m_audioManager;
        CResourceManager m_resourceManager;


        std::list<ILogicSystem *> m_listLogicSystems;
        std::list<IRenderingSystem *> m_listRenderingSystems;


    public:
        // No copying or moving
        CEngine(const CEngine&) = delete;
        CEngine& operator=(const CEngine&) = delete;
        CEngine(CEngine&&) = delete;
        CEngine& operator=(CEngine&&) = delete;
        
        ~CEngine();

        static CEngine& createInstance(CWindow& window, float updateInterval = -1);
        static CEngine& getInstance();
        static void deleteInstance();


        CWindow& getWindow();

        ecs::CEntityWorld& getEntityWorld();

        CEventManager& getEventManager();

        CAudioManager& getAudioManager();

        CResourceManager& getResourceManager();



        // System execution is ordered by ascending priority (the bigger the number the later in order system is processed)
        void attachSystem(ILogicSystem *system);
        void attachSystem(IRenderingSystem *system);

        // Doesn't free the memory from detached systems
        void detachSystem(ILogicSystem *system);
        void detachSystem(IRenderingSystem *system);
        
        // Returns the first found system of that type
        // If doesn't find the system returns nullptr
        template< typename SystemType >
        SystemType *getLogicSystem() const;

        // Returns the first found system of that type
        // If doesn't find the system returns nullptr
        template< typename SystemType >
        SystemType *getRenderingSystem() const;

        void reorderSystems();



        float getGameUpdatesPerSecond();

        double getGameTimeInSeconds();


        // Throws an exception if no logic system has been attached
        void start();

        void stop();

    private:
        // updateInterval:
        //      <= 0 unlocked update rate
        //       > 0 update rate locked to specified interval in seconds
        CEngine(CWindow& window, float updateInterval = -1 );

        void gameLoop();
    };
    
} // namespace chestnut::engine


#include "engine.inl"


