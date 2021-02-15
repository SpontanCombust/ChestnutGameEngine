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

        m_systemList.push_back( m_sdlEventDispatchSystem );
        m_systemList.push_back( m_renderingSystem );

        m_componentDrivenSystemList.push_back( m_renderingSystem );

        m_eventDrivenSystemList.push_back( m_sdlEventDispatchSystem );

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
        for( ISystem *system : m_systemList )
        {
            system->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = m_entityManager.getTypesOfRecentComponents();
        for( IComponentDrivenSystem *cs : m_componentDrivenSystemList )
        {
            if( !recentComponents.empty() )
            {
                if( cs->needsAnyOfComponents( recentComponents ) )
                    cs->fetchComponents( m_entityManager.getComponentDatabase() );
            }

            m_entityManager.clearTypesOfRecentComponents();
        }

        for( IEventDrivenSystem *es : m_eventDrivenSystemList )
        {
            if( es->needsToRaiseEvents() )
            {
                es->raiseEvents( m_eventManager );
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

        for( IComponentDrivenSystem *cs : m_componentDrivenSystemList )
        {
            delete cs;
        }
        m_componentDrivenSystemList.clear();

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
