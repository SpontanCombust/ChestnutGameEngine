#include "engine/main/game/game.hpp"

namespace chestnut
{    
    CChestnutGame::CChestnutGame( CRenderWindow *renderWindow ) 
    {
        m_parentRenderWindow = renderWindow;

        m_isRunning = false;
        m_isSuspended = true;
    }

    bool CChestnutGame::onCreate() 
    {
        m_gameTimer = new CIntervalTimer(0, 1/60.f, true );
        return true;
    }

    bool CChestnutGame::onStart() 
    {
        m_isRunning = true;
        m_isSuspended = false;
        
        m_gameTimer->start();
        while( m_isRunning && !m_isSuspended )
        {
            m_gameTimer->update();
            onUpdate( m_gameTimer->getDeltaTime() );

            //!TEMPORARY
            if( SDL_GetTicks() > 5000 )
                m_isRunning = false;
        }
        return true;
    }

    bool CChestnutGame::onUpdate( float deltaTime ) 
    {
        theWorld.update( deltaTime );
        return true;
    }

    bool CChestnutGame::onSuspend() 
    {
        m_isSuspended = true;
        return true;
    }

    bool CChestnutGame::onEnd() 
    {
        delete m_gameTimer;
        return true;
    }

} // namespace chestnut
