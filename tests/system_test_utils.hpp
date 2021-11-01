#ifndef __CHESTNUT_ENGINE_SYSTEM_TEST_UTILS_H__
#define __CHESTNUT_ENGINE_SYSTEM_TEST_UTILS_H__

#include "../src/chestnut/engine/ecs_impl/system.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener_guard.hpp"

#include <SDL2/SDL_events.h>

#include <memory>

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

#endif // __CHESTNUT_ENGINE_SYSTEM_TEST_UTILS_H__