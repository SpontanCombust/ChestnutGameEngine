#include "system_test_utils.hpp"

#include "../src/chestnut/engine/main/engine.hpp"

using namespace chestnut::engine;

CCloseWindowListeningSystem::CCloseWindowListeningSystem( CEngine& engine ) 
: ISystem( engine )
{
    auto listener = new CEventListener<SDL_QuitEvent>();
    listener->setHandler( &CCloseWindowListeningSystem::onQuitEvent, this );

    m_quitListener = std::shared_ptr<IEventListener>( listener );
    getEngine().getEventManager().registerListener( m_quitListener );
}

event_function CCloseWindowListeningSystem::onQuitEvent( const SDL_QuitEvent& e ) 
{
    getEngine().stop();
}

void CCloseWindowListeningSystem::update( float dt ) 
{

}
