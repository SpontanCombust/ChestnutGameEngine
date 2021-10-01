#include "engine.hpp"

#include "../misc/locked_auto_timer.hpp"
#include "../misc/exception.hpp"

namespace chestnut
{    
    CEngine::CEngine( std::shared_ptr<CWindow> window, float updateInterval )
    {
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

        for( SLogicSystemNode& logicNode : m_listLogicSystemNodes )
        {
            delete logicNode.system;
        }

        for( SRenderingSystemNode& renderingNode : m_listRenderingSystemNodes )
        {
            delete renderingNode.system;
        }
    }

    CWindow& CEngine::getWindow() 
    {
        return *m_window.get();
    }

    ecs::CEntityWorld& CEngine::getEntityWorld() 
    {
        return m_entityWorld;
    }

    CEventManager& CEngine::getEventManager() 
    {
        return m_eventManager;
    }

    void CEngine::start() 
    {
        if( m_listLogicSystemNodes.empty() )
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

                for( SLogicSystemNode& logicNode : m_listLogicSystemNodes )
                {
                    logicNode.system->update( dt );
                }

                for( SRenderingSystemNode& renderingNode : m_listRenderingSystemNodes )
                {
                    renderingNode.system->update( dt );
                    renderingNode.system->render();
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

} // namespace chestnut
