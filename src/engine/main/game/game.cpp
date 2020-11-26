#include "engine/main/game/game.hpp"

namespace chestnut
{    
    CChestnutGame::CChestnutGame( bool lockFramerate )
    : theWorld( theEventManager )
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
        theWorld.update( deltaTime );
    }

    void CChestnutGame::onSuspend() 
    {
        m_isSuspended = true;
    }

    void CChestnutGame::onEnd() 
    {
        delete m_gameTimer;
        super::onEnd();
    }

} // namespace chestnut
