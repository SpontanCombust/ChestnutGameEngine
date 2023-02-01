#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/engine.hpp"
#include "test_utils.hpp"

#include "chestnut/engine/ecs_impl/systems/debug_gui_rendering_system.hpp"
#include "chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "chestnut/engine/ecs_impl/systems/kinematics2d_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_animation_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_collision_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "chestnut/engine/ecs_impl/systems/timer_system.hpp"
#include "chestnut/engine/debug/log.hpp"


using namespace chestnut::engine;

TEST_CASE("DEBUGGING", "[manual]")
{
    const char *testName = "Debug Editor test";
    debug::CLogger::setToFile("engine.log");    

    chestnutInit();
    {
        CWindow window( testName );

        window.setSize({1280, 720});

        CEngine::createInstance( window, 1.f / 60.f );

        CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
        CEngine::getInstance().attachSystem( new CKinematics2DSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
        CEngine::getInstance().attachSystem( new CSimple2DCollisionSystem(SYSTEM_PRIORITY_HIGHEST + 3) );
        CEngine::getInstance().attachSystem( new CSimple2DAnimationSystem(SYSTEM_PRIORITY_HIGHEST + 4) );
        CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );
        CEngine::getInstance().attachSystem( new CDebugGuiRenderingSystem(SYSTEM_PRIORITY_HIGHEST + 1) );

        CEngine::getInstance().start();

        CEngine::deleteInstance();
    }
    chestnutQuit();
}