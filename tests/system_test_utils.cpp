#include "system_test_utils.hpp"

#include "../src/chestnut/engine/main/engine.hpp"

using namespace chestnut::engine;

CCloseWindowListeningSystem::CCloseWindowListeningSystem(systempriority_t prio) 
: ILogicSystem(prio)
{
    auto listener = new CEventListener<SDL_QuitEvent>();
    listener->setHandler( &CCloseWindowListeningSystem::onQuitEvent, this );
    CEngine::getInstance().getEventManager().registerListener( listener );

    m_quitListenerGuard.reset( listener, &CEngine::getInstance().getEventManager() );
}

event_function CCloseWindowListeningSystem::onQuitEvent( const SDL_QuitEvent& e ) 
{
    CEngine::getInstance().stop();
}

void CCloseWindowListeningSystem::update( float dt ) 
{

}
