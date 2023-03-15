#include <catch2/catch.hpp>

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "chestnut/engine/ecs_impl/systems/kinematics2d_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_collision_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_animation_system.hpp"
#include "chestnut/engine/ecs_impl/systems/simple2d_collision_system.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/resources/entity_template_resource.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/misc/locked_manual_timer.hpp"

#include <random>
#include <string>


using namespace chestnut::engine;
using namespace chestnut::ecs;

class CFramesPerSecondDisplaySystem : public ILogicSystem
{
public:
    CLockedManualTimer m_timer;
    int m_frameCount;

    CFramesPerSecondDisplaySystem()
    : m_timer(0, 1.f, true)
    {

    }

    void onAttach() override
    {
        m_timer.start();
        m_frameCount = 0;
    }

    void update(float dt) override
    {
        auto& e = CEngine::getInstance();

        m_frameCount++;
        if(m_timer.tick(dt))
        {
            e.getWindow().setTitle("FPS: " + std::to_string(m_frameCount));

            m_timer.reset();
            m_frameCount = 0;
        }
    }
};

std::random_device rd;
std::mt19937 gen(rd());

TEST_CASE("Engine - efficiency - sprite count", "manual")
{
    std::uniform_int_distribution<> distrx(0, 1920);
    std::uniform_int_distribution<> distry(0, 1000);

    chestnutInit();
    {
        CWindow window("Efficiency test", 1920, 1000);
        auto& engine = CEngine::createInstance(window);
        
        engine.attachSystem(new CInputEventDispatchSystem());
        engine.attachSystem(new CKinematics2DSystem());
        engine.attachSystem(new CFramesPerSecondDisplaySystem());

        auto renderingSys = new CSimple2DRenderingSystem();
        renderingSys->getCamera().m_position = {960, 500};
        engine.attachSystem(renderingSys);

        auto entTemplExp = CEntityTemplateResource::load(assetPathToAbsolute("testing/entities/efficiencyTestCount.ent"));
        REQUIRE(entTemplExp.has_value());
        auto entTempl = entTemplExp.value();

        const int ENT_COUNT = 1000;
        for (int i = 0; i < ENT_COUNT; i++)
        {
            auto entExp = entTempl->createEntity();

            auto& transform = engine.getEntityWorld().getComponent<CTransform2DComponent>(entExp.value()).get();
            transform.position = {
                (float)distrx(gen),
                (float)distry(gen)
            };
        }

        engine.start();

        CEngine::deleteInstance();
    }
    chestnutQuit();
}




TEST_CASE("Engine - efficiency - collider count", "manual")
{
    std::uniform_int_distribution<> distrx(0, 800);
    std::uniform_int_distribution<> distry(0, 600);

    chestnutInit();
    {
        CWindow window("Efficiency test", 800, 600);
        auto& engine = CEngine::createInstance(window);
        
        engine.attachSystem(new CInputEventDispatchSystem());
        engine.attachSystem(new CKinematics2DSystem());
        engine.attachSystem(new CFramesPerSecondDisplaySystem());
        engine.attachSystem(new CSimple2DCollisionSystem());
        
        auto renderingSys = new CSimple2DRenderingSystem();
        renderingSys->getCamera().m_position = {400, 300};
        engine.attachSystem(renderingSys);


        auto entTemplExp = CEntityTemplateResource::load(assetPathToAbsolute("testing/entities/efficiencyTestCollisions.ent"));
        REQUIRE(entTemplExp.has_value());
        auto entTempl = entTemplExp.value();

        const int ENT_COUNT = 100;
        for (int i = 0; i < ENT_COUNT; i++)
        {
            auto entExp = entTempl->createEntity();

            auto& transform = engine.getEntityWorld().getComponent<CTransform2DComponent>(entExp.value()).get();
            transform.position = {
                (float)distrx(gen),
                (float)distry(gen)
            };
        }

        engine.start();

        CEngine::deleteInstance();
    }
    chestnutQuit();
}