#include "chestnut/engine/main/engine.hpp"

#include "chestnut/engine/misc/locked_auto_timer.hpp"
#include "chestnut/engine/misc/exception.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <algorithm>


namespace chestnut::engine
{    
    CEngine *CEngine::sm_instance = nullptr;


    CEngine::CEngine( CWindow* window, float updateInterval )
    {
        if( !window )
        {
            LOG_WARNING( "Null window pointer passed to the engine" );
        }
        
        m_window = window;

        if( updateInterval <= 0 )
        {
            m_updateTimer = new CAutoTimer(0);
        }
        else
        {
            CLockedAutoTimer *lockedTimer = new CLockedAutoTimer( 0, updateInterval, true );
            lockedTimer->toggleThreadWaitingForTimerInterval( true );
            m_updateTimer = lockedTimer;
        }

        m_isRunning = false;
    }

    CEngine::~CEngine() 
    {
        delete m_updateTimer;

        // for( ISystem *sys : m_listLogicSystems )
        // {
        //     delete sys;
        // }

        // for( IRenderingSystem  *sys : m_listRenderingSystems )
        // {
        //     delete sys;
        // }
    }




    void CEngine::createInstance(CWindow* window, float updateInterval)
    {
        if(sm_instance != nullptr)
        {
            delete sm_instance;
        }

        sm_instance = new CEngine(window, updateInterval);
    }

    CEngine& CEngine::getInstance()
    {
        return *sm_instance;
    }

    void CEngine::deleteInstance()
    {
        if(sm_instance != nullptr)
        {
            delete sm_instance;
            sm_instance = nullptr;
        }
    }




    CWindow& CEngine::getWindow() 
    {
        return *m_window;
    }

    ecs::CEntityWorld& CEngine::getEntityWorld() 
    {
        return m_entityWorld;
    }

    CEventManager& CEngine::getEventManager() 
    {
        return m_eventManager;
    }

    CAudioManager& CEngine::getAudioManager() 
    {
        return m_audioManager;
    }




    void CEngine::attachSystem(ILogicSystem *system)
    {
        // search for the spot where to insert the system
        auto it = m_listLogicSystems.begin();
        for( ;it != m_listLogicSystems.end(); ++it )
        {
            if( (*it)->getPriority() > system->getPriority() )
            {
                break;
            }
        }

        m_listLogicSystems.insert( it, system );
    }

    void CEngine::attachSystem(IRenderingSystem *system)
    {
        // search for the spot where to insert the system
        auto it = m_listRenderingSystems.begin();
        for( ;it != m_listRenderingSystems.end(); ++it )
        {
            if( (*it)->getPriority() > system->getPriority() )
            {
                break;
            }
        }

        m_listRenderingSystems.insert( it, system );
    }

    void CEngine::detachSystem(ILogicSystem *system)
    {
        for(auto it = m_listLogicSystems.begin(); it != m_listLogicSystems.end(); ++it)
        {
            if(*it == system)
            {
                m_listLogicSystems.erase(it);
                return;
            }
        }       
    }

    void CEngine::detachSystem(IRenderingSystem *system)
    {
        for(auto it = m_listRenderingSystems.begin(); it != m_listRenderingSystems.end(); ++it)
        {
            if(*it == system)
            {
                m_listRenderingSystems.erase(it);
                return;
            }
        }       
    }

    void CEngine::reorderSystems()
    {
        std::stable_sort(
            m_listLogicSystems.begin(),
            m_listLogicSystems.end(),

            [](const ILogicSystem *s1, const ILogicSystem *s2) {
                return s1->getPriority() < s2->getPriority();
            }
        );

        std::stable_sort(
            m_listRenderingSystems.begin(),
            m_listRenderingSystems.end(),

            [](const IRenderingSystem *s1, const IRenderingSystem *s2) {
                return s1->getPriority() < s2->getPriority();
            }
        );
    }




    void CEngine::start() 
    {
        if( m_listLogicSystems.empty() )
        {
            throw ChestnutException( "Engine needs at least one logic system to control it!");
        }

        m_isRunning = true;
        m_updateTimer->start();  
        gameLoop();
    }

    void CEngine::gameLoop() 
    {
        while( m_isRunning )
        {
            if( m_updateTimer->tick() )
            {
                float dt = m_updateTimer->getDeltaTime();

                for( ILogicSystem *sys : m_listLogicSystems )
                {
                    sys->update( dt );
                }

                for( IRenderingSystem  *sys : m_listRenderingSystems )
                {
                    sys->render();
                }
            }
        }
    }

    void CEngine::stop()
    {
        m_isRunning = false;
    }

    float CEngine::getGameUpdatesPerSecond() 
    {
        return m_updateTimer->getUpdatesPerSec();
    }

    double CEngine::getGameTimeInSeconds() 
    {
        return m_updateTimer->getElapsedTimeInSeconds();
    }

} // namespace chestnut::engine
