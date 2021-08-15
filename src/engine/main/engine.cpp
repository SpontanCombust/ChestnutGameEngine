#include "engine.hpp"

namespace chestnut
{    
    CEngine::CEngine()
    {
        m_wasInit                   = false;

        m_logicUpdateTimer          = nullptr;

        m_isRunning                 = false;
        m_isSuspended               = true;

        m_sdlEventDispatchSystem    = nullptr;
        m_timerSystem               = nullptr;
        m_kinematicsSystem          = nullptr;
        m_renderingSystem           = nullptr;
    }

    CEngine::~CEngine() 
    {
        destroy();
    }

    void CEngine::init( float renderInterval, float updateInterval ) 
    {
        if( !m_wasInit )
        {
            if( updateInterval < 0 )
            {
                m_logicUpdateTimer = new CAutoTimer(0);
            }
            else
            {
                CLockedAutoTimer *lockedTimer = new CLockedAutoTimer( 0, updateInterval, true );
                lockedTimer->toggleThreadWaitingForTimerInterval( true );
                m_logicUpdateTimer = lockedTimer;
            }

            if( renderInterval < 0 )
            {
                m_renderTimer = new CAutoTimer(1);
            }
            else
            {
                m_renderTimer = new CLockedAutoTimer( 1, renderInterval, true );
            }
            

            //TODO do system submition mechanism to engine
            m_sdlEventDispatchSystem = new CSDLEventDispatchSystem();
            m_timerSystem = new CTimerSystem();
            m_kinematicsSystem = new CKinematicsSystem();
            m_renderingSystem = new CRenderingSystem();

            m_systemsList.push_back( m_sdlEventDispatchSystem );
            m_systemsList.push_back( m_timerSystem );
            m_systemsList.push_back( m_kinematicsSystem );
            m_systemsList.push_back( m_renderingSystem );

            m_componentSystemsList.push_back( m_timerSystem );
            m_componentSystemsList.push_back( m_kinematicsSystem );
            m_componentSystemsList.push_back( m_renderingSystem );

            registerQuitEvent();

            m_wasInit = true;
        }
    }

    void CEngine::start() 
    {
        m_isRunning = true;
        m_isSuspended = false;

        for( IComponentSystem *compSys : m_componentSystemsList )
        {
            compSys->initQueries();
        } 
        
        if( m_wasInit )
        {
            m_logicUpdateTimer->start();
            m_renderTimer->start();   
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
            uint32_t dt = m_logicUpdateTimer->getDeltaTime();
            
            if( m_logicUpdateTimer->tick() )
            {
                update(dt);
            }

            if( m_renderTimer->tick() )
            {
                m_renderingSystem->render();
            }
        }
    }

    void CEngine::update( uint32_t deltaTime ) 
    {
        // clearing outdated batches from systems
        std::vector< ecs::SEntityQuery * > vecQueries;
        for( IComponentSystem *compSys : m_componentSystemsList )
        {
            vecQueries = compSys->getEntityQueries();
            for( ecs::SEntityQuery *query : vecQueries )
            {
                entityWorld.queryEntities( *query );
            }
        }    

        // updating systems
        for( ISystem *sys : m_systemsList )
        {
            // TODO exclude rendering system
            sys->update( deltaTime );
        }

        // updating event manager
        eventManager.delegateEvents();
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
        delete m_logicUpdateTimer;

        delete m_renderingSystem;
        delete m_timerSystem;
        delete m_sdlEventDispatchSystem;

        m_systemsList.clear();
        m_componentSystemsList.clear();

        unregisterQuitEvent();
        eventManager.clearListeners();
    }

    float CEngine::getGameUpdatesPerSecond() 
    {
        return m_logicUpdateTimer->getAvgUpdatesPerSec();
    }

    float CEngine::getGameTimeInSeconds() 
    {
        return m_logicUpdateTimer->getCurrentTimeInSeconds();
    }



    event_function CEngine::onQuitEvent( const SQuitRequestEvent& event ) 
    {
        stop();
    }

    void CEngine::registerQuitEvent() 
    {
        m_quitListenerID = eventManager.registerListener( this, &CEngine::onQuitEvent );
    }

    void CEngine::unregisterQuitEvent() 
    {
        eventManager.unregisterListenerByID< SQuitRequestEvent >( m_quitListenerID );
    }

} // namespace chestnut
