#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/debug/log.hpp"
#include "../src/chestnut/engine/ecs_impl/system.hpp"
#include "../src/chestnut/engine/resources/animation2d_resource.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_animation_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "../src/chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"

#include <SDL_events.h>


using namespace chestnut::ecs;
using namespace chestnut::engine;

enum EAnimType
{
    WALK_UP,
    WALK_DOWN,
    WALK_LEFT,
    WALK_RIGHT,
    ANIM_COUNT
};

const char *animTypeToAnimName( EAnimType type )
{
    switch( type )
    {
    case WALK_UP:
        return "walk_up";
    case WALK_DOWN:
        return "walk_down";
    case WALK_LEFT:
        return "walk_left";
    case WALK_RIGHT:
        return "walk_right";
    default:
        return "walk_up";
    }
}

class CAnimationDemoSystem : public ILogicSystem
{
public:
    entityid_t ent;
    int animType = WALK_UP;

    CAnimationDemoSystem(systempriority_t prio)
    : ILogicSystem(prio)
    {
        auto& engine = CEngine::getInstance();

        ent = engine.getEntityWorld().createEntity();

        auto transformHandle = engine.getEntityWorld().createComponent<CTransform2DComponent>( ent );
        transformHandle->position = vecCastType<float>(engine.getWindow().getSize()) / 2.f;

        auto modelHandle = engine.getEntityWorld().createComponent<CModel2DComponent>( ent );
        modelHandle->size = vec2f{ 200.f, 200.f };

        auto textureHandle = engine.getEntityWorld().createComponent<CSpriteComponent>( ent );
        CSprite sprite;
        REQUIRE_NOTHROW( sprite = CSprite( CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/player_sheet_orig.png" ).value() ) );
        sprite.setFiltering( GL_NEAREST, GL_NEAREST );
        textureHandle->sprite = sprite;

        auto animHandle = engine.getEntityWorld().createComponent<CAnimation2DComponent>( ent );
        auto animResource = CAnimation2DResource::load(CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/animations/player_sheet_orig.anim");
        REQUIRE_NOTHROW(animHandle->animationResource = animResource.value());
        
        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CAnimationDemoSystem::handleInput, this );
        l->setFilter( 
            []( const SDL_KeyboardEvent& e ) -> bool
            {
                return e.type == SDL_KEYDOWN;
            }
        );

        addEventListener("handleInput", l);
    }

    ~CAnimationDemoSystem()
    {
        CEngine::getInstance().getEntityWorld().destroyEntity( ent );
    }

    void update( float dt ) override
    {

    }

    event_function handleInput( const SDL_KeyboardEvent& e )
    {
        auto animHandle = CEngine::getInstance().getEntityWorld().getComponent<CAnimation2DComponent>( ent );

        switch( e.keysym.sym )
        {
        case SDLK_LEFT:
            animType = ( animType - 1 >= 0 ) ? animType - 1 : ANIM_COUNT - 1;
            animHandle->playAnimation( animTypeToAnimName( (EAnimType)animType ) );
            break;
        case SDLK_RIGHT:
            animType = ( animType + 1 < ANIM_COUNT ) ? animType + 1 : 0;
            animHandle->playAnimation( animTypeToAnimName( (EAnimType)animType ) );
            break;
        case SDLK_UP:
            animHandle->animSpeedMultiplier += 0.1f;
            break;
        case SDLK_DOWN:
            animHandle->animSpeedMultiplier -= 0.1f;
            break;
        case SDLK_SPACE:
            animHandle->isAnimPaused = !animHandle->isAnimPaused;
            break;
        case SDLK_ESCAPE:
            animHandle->stopAnimation();
            break;
        }
    }
};


TEST_CASE( "Systems - Simple2D animation system test", "[manual][demo]" )
{
    const char *testName = "Simple2D animation system test";

    chestnutInit();
    debug::CLogger::setToFile("engine.log");

    CWindow window( testName );

    CEngine::createInstance( window, 1.f / 60.f );

    CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
    CEngine::getInstance().attachSystem( new CSimple2DAnimationSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
    CEngine::getInstance().attachSystem( new CAnimationDemoSystem(SYSTEM_PRIORITY_HIGHEST + 3) );
    CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );

    showInfoMessageBox( testName,
        "left/right - change animation\n"
        "up/down - change playback speed\n"
        "space - pause/resume\n"
        "esc - stop\n"
    );

    CEngine::getInstance().start();

    CEngine::deleteInstance();
    chestnutQuit();
}
