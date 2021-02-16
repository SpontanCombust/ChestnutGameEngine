#include "game.hpp"

namespace chestnut
{    
    CChestnutGame::CChestnutGame( bool lockFramerate )
    {
        m_lockFramerate = lockFramerate;
        m_isRunning = false;
        m_isSuspended = true;
    }

    bool CChestnutGame::onCreate() 
    {
        bool valid = super::onCreate();

        if( m_lockFramerate )
            m_gameUpdateTimer = new CLockedTimer(0, 1/60.f, true );
        else
            m_gameUpdateTimer = new CTimer(0);


        m_sdlEventDispatchSystem = new CSDLEventDispatchSystem();
        m_renderingSystem = new CRenderingComponentSystem();

        m_updatableSystemsList.push_back( m_sdlEventDispatchSystem );
        m_updatableSystemsList.push_back( m_renderingSystem );

        m_componentFetchingSystemsList.push_back( m_renderingSystem );

        m_eventRaisingSystemsList.push_back( m_sdlEventDispatchSystem );

        registerQuitEvent();

        return valid;
    }

    void CChestnutGame::onStart() 
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

    void CChestnutGame::onUpdate( float deltaTime ) 
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

        for( IEventRaisingSystem *ers : m_eventRaisingSystemsList )
        {
            if( ers->needsToRaiseEvents() )
            {
                ers->raiseEvents( m_eventManager );
            }
        }

        // drawing the frame
        m_renderingSystem->draw();
    }

    void CChestnutGame::onSuspend() 
    {
        m_isSuspended = true;
    }

    void CChestnutGame::onEnd() 
    {
        delete m_gameUpdateTimer;

        delete m_renderingSystem;
        delete m_sdlEventDispatchSystem;

        m_updatableSystemsList.clear();
        m_componentFetchingSystemsList.clear();
        m_eventRaisingSystemsList.clear();

        unregisterQuitEvent();
        m_eventManager.clearListeners();
        
        m_entityManager.destroyAllEntities();

        super::onEnd();
    }

    CEntityManager& CChestnutGame::getEntityManager() 
    {
        return m_entityManager;
    }

    CEventManager& CChestnutGame::getEventManager() 
    {
        return m_eventManager;
    }

    float CChestnutGame::getGameTimeInSeconds() 
    {
        return m_gameUpdateTimer->getCurrentTimeInSeconds();
    }


    event_function CChestnutGame::onQuitEvent( const SMiscSDLEvent& event ) 
    {
        m_isRunning = false;
    }

    void CChestnutGame::registerQuitEvent() 
    {
        m_quitListenerID = m_eventManager.registerListener( this, &CChestnutGame::onQuitEvent );

        m_eventManager.constrainListenerByID< SMiscSDLEvent >( m_quitListenerID,
            []( const SMiscSDLEvent& event ) -> bool
            {
                return event.sdlEvent.type == SDL_QUIT;
            }
        );
    }

    void CChestnutGame::unregisterQuitEvent() 
    {
        m_eventManager.unregisterListenerByID< SMiscSDLEvent >( m_quitListenerID );
    }

} // namespace chestnut
