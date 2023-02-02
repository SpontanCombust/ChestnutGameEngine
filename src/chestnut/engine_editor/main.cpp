#pragma warning(disable : 4005) // ignore APIENTRY redefinition

#include <chestnut/engine/init.hpp>
#include <chestnut/engine/debug/log.hpp>
#include <chestnut/engine/main/engine.hpp>
#include <chestnut/engine/ecs_impl/systems/debug_gui_rendering_system.hpp>
#include <chestnut/engine/ecs_impl/systems/garbage_collector_system.hpp>
#include <chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp>
#include <chestnut/engine/ecs_impl/systems/kinematics2d_system.hpp>
#include <chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp>
#include <chestnut/engine/ecs_impl/systems/simple2d_animation_system.hpp>
#include <chestnut/engine/ecs_impl/systems/simple2d_collision_system.hpp>
#include <chestnut/engine/ecs_impl/systems/timer_system.hpp>
#include <chestnut/engine/misc/utility_functions.hpp>
#include <windows.h>


using namespace chestnut::engine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try
    {
        debug::CLogger::setToFile("editor.log");

        chestnutInit();
        {
            CWindow window(
                CWindowAttribs("Chestnut Editor")
                .width(1280)
                .height(720)
                .position({100, 100})
                .vsync(true)
            );

            CEngine::createInstance(window, 1.f/60.f);
            auto& engine = CEngine::getInstance();

            engine.attachSystem(new CInputEventDispatchSystem());
            engine.attachSystem(new CKinematics2DSystem());
            engine.attachSystem(new CSimple2DCollisionSystem());
            engine.attachSystem(new CSimple2DAnimationSystem());
            engine.attachSystem(new CTimerSystem());
            engine.attachSystem(new CGarbageCollectorSystem());

            engine.attachSystem(new CSimple2DRenderingSystem());
            engine.attachSystem(new CDebugGuiRenderingSystem());

            engine.start();

            CEngine::deleteInstance();
        }
        chestnutQuit();
    }
    catch(const std::exception& e)
    {
        messageBoxInfo(e.what());
        return -1;
    }

    return 0;
}
