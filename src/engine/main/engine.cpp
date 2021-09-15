#include "engine.hpp"

#include "../misc/timers/locked_auto_timer.hpp"
#include "../debug/debug.hpp"
#include "../ecs/systems/systems.hpp"
#include "../ecs/events/quit_request_event.hpp"

namespace chestnut
{    
    CEngine::CEngine( CWindow& window ) : m_window( window )
    {
        m_wasInit       = false;
        m_isRunning     = false;
        m_isSuspended   = true;

        m_updateTimer   = nullptr;
    }

    CEngine::~CEngine() 
    {
        destroy();
    }

    CWindow& CEngine::getWindow() 
    {
        return m_window;
    }

    ecs::CEntityWorld& CEngine::getEntityWorld() 
    {
        return m_entityWorld;
    }

    CEventManager& CEngine::getEventManager() 
    {
        return m_eventManager;
    }

    void CEngine::init( float updateInterval ) 
    {
        if( !m_wasInit )
        {
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

            //TODO do system submition mechanism to engine
            m_systemsList.push_back( new CSDLEventDispatchSystem( *this ) );
            m_systemsList.push_back( new CTimerSystem( *this ) );
            m_systemsList.push_back( new CKinematicsSystem( *this ) );
            m_systemsList.push_back( new CRenderingSystem( *this ) );

            registerQuitEvent();

            m_wasInit = true;
        }
    }

    void CEngine::start() 
    {
        m_isRunning = true;
        m_isSuspended = false;

        if( m_wasInit )
        {
            m_updateTimer->start();  
            gameLoop();
        }
        else
        {
            LOG_CHANNEL( "CEngine", "The engine was not initialized!" );
        }
    }

    void CEngine::gameLoop() 
    {
        while( m_isRunning )
        {
            uint32_t dt = m_updateTimer->getDeltaTime();
            
            if( m_updateTimer->tick() )
            {
                for( ISystem *sys : m_systemsList )
                {
                    // TODO implement system pipeline configuration
                    sys->update( dt );
                }
            }
        }
    }

    void CEngine::suspend() 
    {
        m_isSuspended = true;
    }

    void CEngine::stop()
    {
        m_isRunning = false;
    }

    void CEngine::destroy() 
    {
        delete m_updateTimer;

        for( ISystem *system : m_systemsList )
        {
            delete system;
        }
    }

    float CEngine::getGameUpdatesPerSecond() 
    {
        return m_updateTimer->getAvgUpdatesPerSec();
    }

    float CEngine::getGameTimeInSeconds() 
    {
        return m_updateTimer->getCurrentTimeInSeconds();
    }



    void CEngine::registerQuitEvent() 
    {
        auto quitEventListener = new CEventListener<SQuitRequestEvent>(
            [this]( const SQuitRequestEvent& e ) 
            { 
                stop(); 
            }
        );

        m_quitEventListener = std::shared_ptr<IEventListener>( quitEventListener );

        m_eventManager.registerListener( m_quitEventListener );
    }

} // namespace chestnut
