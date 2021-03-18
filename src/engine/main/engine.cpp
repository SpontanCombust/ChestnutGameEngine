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

        m_systemsList.push_back( m_sdlEventDispatchSystem );
        m_systemsList.push_back( m_timerSystem );
        m_systemsList.push_back( m_renderingSystem );

        m_componentSystemsList.push_back( m_timerSystem );
        m_componentSystemsList.push_back( m_renderingSystem );

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
        for( ISystem *sys : m_systemsList )
        {
            sys->update( deltaTime );
        }

        // fetching new components to component systems
        std::list< std::type_index > recentComponents = entityManager.getTypesOfRecentComponents();
        for( IComponentSystem *compSys : m_componentSystemsList )
        {
            if( !recentComponents.empty() )
            {
                if( compSys->needsAnyOfComponents( recentComponents ) )
                    compSys->fetchComponents( entityManager.getComponentDatabase() );
            }

            entityManager.clearTypesOfRecentComponents();
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

        m_systemsList.clear();
        m_componentSystemsList.clear();

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
