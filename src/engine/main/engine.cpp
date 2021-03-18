#include "engine.hpp"

namespace chestnut
{    
    CEngine::CEngine()
    {
        m_gameUpdateTimer           = nullptr;

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

    void CEngine::init( bool lockFramerate ) 
    {
        if( lockFramerate )
            m_gameUpdateTimer = new CLockedTimer(0, 1/60.f, true );
        else
            m_gameUpdateTimer = new CTimer(0);


        m_sdlEventDispatchSystem = new CSDLEventDispatchSystem();
        m_timerSystem = new CTimerSystem();
        m_renderingSystem = new CRenderingSystem();

        m_updatableSystemsList.push_back( m_sdlEventDispatchSystem );
        m_updatableSystemsList.push_back( m_timerSystem );
        m_updatableSystemsList.push_back( m_renderingSystem );

        m_componentFetchingSystemsList.push_back( m_timerSystem );
        m_componentFetchingSystemsList.push_back( m_renderingSystem );

        m_eventRaisingSystemsList.push_back( m_sdlEventDispatchSystem );
        m_eventRaisingSystemsList.push_back( m_timerSystem );

        registerQuitEvent();
    }

    void CEngine::start() 
    {
        m_isRunning = true;
        m_isSuspended = false;
        
        m_gameUpdateTimer->start();
        while( m_isRunning )
        {
            if( m_gameUpdateTimer->update() )
                update( m_gameUpdateTimer->getDeltaTime() );
        }
    }

    void CEngine::update( float deltaTime ) 
    {
        // updating event manager
        eventManager.delegateEvents();

        // updating systems
        for( IUpdatableSystem *us : m_updatableSystemsList )
        {
            us->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = entityManager.getTypesOfRecentComponents();
        for( IComponentFetchingSystem *cfs : m_componentFetchingSystemsList )
        {
            if( !recentComponents.empty() )
            {
                if( cfs->needsAnyOfComponents( recentComponents ) )
                    cfs->fetchComponents( entityManager.getComponentDatabase() );
            }

            entityManager.clearTypesOfRecentComponents();
        }

        for( CEventRaisingSystem *ers : m_eventRaisingSystemsList )
        {
            if( ers->needsToRaiseEvents() )
            {
                ers->raiseEvents( eventManager );
            }
        }

        // drawing the frame
        m_renderingSystem->draw();
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
        delete m_gameUpdateTimer;

        delete m_renderingSystem;
        delete m_timerSystem;
        delete m_sdlEventDispatchSystem;

        m_updatableSystemsList.clear();
        m_componentFetchingSystemsList.clear();
        m_eventRaisingSystemsList.clear();

        unregisterQuitEvent();
        eventManager.clearListeners();
        
        entityManager.destroyAllEntities();
    }

    float CEngine::getGameTimeInSeconds() 
    {
        return m_gameUpdateTimer->getCurrentTimeInSeconds();
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
