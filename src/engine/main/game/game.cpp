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


        m_renderingSystem = new CRenderingComponentSystem();

        m_systemList.push_back( m_renderingSystem );

        m_componentSystemList.push_back( m_renderingSystem );


        return valid;
    }

    void CChestnutGame::onStart() 
    {
        super::onStart();

        m_isRunning = true;
        m_isSuspended = false;
        
        m_gameUpdateTimer->start();
        while( m_isRunning && !m_isSuspended )
        {
            if( m_gameUpdateTimer->update() )
                onUpdate( m_gameUpdateTimer->getDeltaTime() );

            //!TEMPORARY
            if( SDL_GetTicks() > 5000 )
                m_isRunning = false;
        }
    }

    void CChestnutGame::onUpdate( float deltaTime ) 
    {
        // updating event manager
        theEventManager.update( deltaTime );

        // updating systems
        for( ISystem *system : m_systemList )
        {
            system->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = theEntityManager.getTypesOfRecentComponents();
        for( IComponentSystem *cs : m_componentSystemList )
        {
            if( !recentComponents.empty() )
            {
                if( cs->needsAnyOfComponents( recentComponents ) )
                    cs->fetchComponents( theEntityManager.getComponentDatabase() );
            }

            theEntityManager.clearTypesOfRecentComponents();
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

        for( IComponentSystem *cs : m_componentSystemList )
        {
            delete cs;
        }
        m_componentSystemList.clear();

        theEventManager.clearListeners();
        
        theEntityManager.destroyAllEntities();

        super::onEnd();
    }

} // namespace chestnut
