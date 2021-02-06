#include "engine/main/game/game.hpp"

namespace chestnut
{    
    CChestnutGame::CChestnutGame( bool lockFramerate )
    : theEntityManager( theEventManager )
    {
        m_lockFramerate = lockFramerate;
        m_isRunning = false;
        m_isSuspended = true;
    }

    bool CChestnutGame::onCreate() 
    {
        bool valid = super::onCreate();

        if( m_lockFramerate )
            m_gameTimer = new CIntervalTimer(0, 1/60.f, true );
        else
            m_gameTimer = new CTimer(0);

        m_componentSystemList.push_back( new CRenderingComponentSystem() );

        return valid;
    }

    void CChestnutGame::onStart() 
    {
        super::onStart();

        m_isRunning = true;
        m_isSuspended = false;
        
        m_gameTimer->start();
        while( m_isRunning && !m_isSuspended )
        {
            if( m_gameTimer->update() )
                onUpdate( m_gameTimer->getDeltaTime() );

            //!TEMPORARY
            if( SDL_GetTicks() > 5000 )
                m_isRunning = false;
        }
    }

    void CChestnutGame::onUpdate( float deltaTime ) 
    {
        // updating event manager
        theEventManager.update( deltaTime );

        // updating component systems
        std::list< std::type_index > recentComponents = theEntityManager.getTypesOfRecentComponents();
        for( IComponentSystem *cs : m_componentSystemList )
        {
            cs->update( deltaTime );

            if( !recentComponents.empty() )
            {
                if( cs->needsAnyOfComponents( recentComponents ) )
                    cs->fetchComponents( theEntityManager.getComponentDatabase() );
            }

            theEntityManager.clearTypesOfRecentComponents();
        }
    }

    void CChestnutGame::onSuspend() 
    {
        m_isSuspended = true;
    }

    void CChestnutGame::onEnd() 
    {
        delete m_gameTimer;

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
