#pragma once


#include "../src/chestnut/engine/ecs_impl/system.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener_guard.hpp"

#include <SDL_events.h>

class CCloseWindowListeningSystem : public chestnut::engine::ISystem
{
private:
    chestnut::engine::CEventListenerGuard m_quitListenerGuard;

public:
    CCloseWindowListeningSystem( chestnut::engine::CEngine& engine );

    void update( float dt );

private:
    chestnut::engine::event_function onQuitEvent( const SDL_QuitEvent& e );
};

