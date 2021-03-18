#include "engine.hpp"

namespace chestnut
{    
    CEngine::CEngine( bool lockFramerate )
    {
        m_lockFramerate = lockFramerate;
        m_isRunning = false;
        m_isSuspended = true;
    }

    bool CEngine::onCreate() 
    {
        bool valid = super::onCreate();

        if( m_lockFramerate )
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

        return valid;
    }

    void CEngine::onStart() 
    {
        super::onStart();

        m_isRunning = true;
        m_isSuspended = false;
        
        m_gameUpdateTimer->start();
        while( m_isRunning )
        {
            if( m_gameUpdateTimer->update() )
                onUpdate( m_gameUpdateTimer->getDeltaTime() );
        }
    }

    void CEngine::onUpdate( float deltaTime ) 
    {
        // updating event manager
        m_eventManager.delegateEvents();

        // updating systems
        for( IUpdatableSystem *us : m_updatableSystemsList )
        {
            us->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = m_entityManager.getTypesOfRecentComponents();
        for( IComponentFetchingSystem *cfs : m_componentFetchingSystemsList )
        {
            if( !recentComponents.empty() )
            {
                if( cfs->needsAnyOfComponents( recentComponents ) )
                    cfs->fetchComponents( m_entityManager.getComponentDatabase() );
            }

            m_entityManager.clearTypesOfRecentComponents();
        }

        for( CEventRaisingSystem *ers : m_eventRaisingSystemsList )
        {
            if( ers->needsToRaiseEvents() )
            {
                ers->raiseEvents( m_eventManager );
            }
        }

        // drawing the frame
        m_renderingSystem->draw();
    }

    void CEngine::onSuspend() 
    {
        m_isSuspended = true;
    }

    void CEngine::onEnd() 
    {
        delete m_gameUpdateTimer;

        delete m_renderingSystem;
        delete m_timerSystem;
        delete m_sdlEventDispatchSystem;

        m_updatableSystemsList.clear();
        m_componentFetchingSystemsList.clear();
        m_eventRaisingSystemsList.clear();

        unregisterQuitEvent();
        m_eventManager.clearListeners();
        
        m_entityManager.destroyAllEntities();

        super::onEnd();
    }

    CEntityManager& CEngine::getEntityManager() 
    {
        return m_entityManager;
    }

    CEventManager& CEngine::getEventManager() 
    {
        return m_eventManager;
    }

    float CEngine::getGameTimeInSeconds() 
    {
        return m_gameUpdateTimer->getCurrentTimeInSeconds();
    }



    event_function CEngine::onQuitEvent( const SQuitRequestEvent& event ) 
    {
        m_isRunning = false;
    }

    void CEngine::registerQuitEvent() 
    {
        m_quitListenerID = m_eventManager.registerListener( this, &CEngine::onQuitEvent );
    }

    void CEngine::unregisterQuitEvent() 
    {
        m_eventManager.unregisterListenerByID< SQuitRequestEvent >( m_quitListenerID );
    }

} // namespace chestnut
