#include "system_test_utils.hpp"

#include "../src/chestnut/engine/main/engine.hpp"

using namespace chestnut::engine;

CCloseWindowListeningSystem::CCloseWindowListeningSystem( CEngine& engine ) 
: ISystem( engine )
{
    auto listener = new CEventListener<SDL_QuitEvent>();
    listener->setHandler( &CCloseWindowListeningSystem::onQuitEvent, this );
    getEngine().getEventManager().registerListener( listener );

    m_quitListenerGuard.reset( listener, &getEngine().getEventManager() );
}

event_function CCloseWindowListeningSystem::onQuitEvent( const SDL_QuitEvent& e ) 
{
    getEngine().stop();
}

void CCloseWindowListeningSystem::update( float dt ) 
{

}
