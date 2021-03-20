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
                m_logicUpdateTimer = new CTimer(0);
            }
            else
            {
                m_logicUpdateTimer = new CLockedTimer( 0, updateInterval, true );
            }

            if( renderInterval < 0 )
            {
                m_renderTimer = new CTimer(1);
            }
            else
            {
                m_renderTimer = new CLockedTimer( 1, renderInterval, true );
            }
            


            m_sdlEventDispatchSystem = new CSDLEventDispatchSystem();
            m_timerSystem = new CTimerSystem();
            m_renderingSystem = new CRenderingSystem();

            m_systemsList.push_back( m_sdlEventDispatchSystem );
            m_systemsList.push_back( m_timerSystem );
            m_systemsList.push_back( m_renderingSystem );

            m_componentSystemsList.push_back( m_timerSystem );
            m_componentSystemsList.push_back( m_renderingSystem );

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
            m_logicUpdateTimer->start();
            while( m_isRunning )
            {
                if( m_logicUpdateTimer->update() )
                    update( m_logicUpdateTimer->getDeltaTime() );
            }
        }
        else
        {
            LOG_CHANNEL( "CEngine", "The engine was not initialized!" );
        }
    }

    void CEngine::update( float deltaTime ) 
    {
        // updating event manager
        eventManager.delegateEvents();

        // updating systems
        for( ISystem *sys : m_systemsList )
        {
            // TODO exclude rendering system
            sys->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = entityManager.getTypesOfRecentComponents();
        if( !recentComponents.empty() )
        {
            for( IComponentSystem *compSys : m_componentSystemsList )
            {
                if( compSys->needsAnyOfComponents( recentComponents ) )
                    compSys->fetchComponents( entityManager.getComponentDatabase() );
            }
        }
        entityManager.clearTypesOfRecentComponents();

        if( m_renderTimer->update() )
        {
            // drawing the frame
            m_renderingSystem->draw();
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
        delete m_logicUpdateTimer;

        delete m_renderingSystem;
        delete m_timerSystem;
        delete m_sdlEventDispatchSystem;

        m_systemsList.clear();
        m_componentSystemsList.clear();

        unregisterQuitEvent();
        eventManager.clearListeners();
        
        entityManager.destroyAllEntities();
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
