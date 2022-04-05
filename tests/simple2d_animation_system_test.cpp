#include <catch2/catch.hpp>

#include "test_utils.hpp"
#include "system_test_utils.hpp"

#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/ecs_impl/system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_animation_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "../src/chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener_guard.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/init.hpp"

#include <SDL2/SDL_events.h>


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

class CAnimationDemoSystem : public ISystem
{
public:
    entityid_t ent;
    CEventListenerGuard listenerGuard;

    int animType = WALK_UP;

    CAnimationDemoSystem( CEngine& engine )
    : ISystem( engine )
    {
        ent = engine.getEntityWorld().createEntity();

        auto transformHandle = engine.getEntityWorld().createComponent<CTransform2DComponent>( ent );
        transformHandle->position = vec2f{ engine.getWindow().getSizeWidth() / 2.f, engine.getWindow().getSizeHeight() / 2.f };

        auto modelHandle = engine.getEntityWorld().createComponent<CModel2DComponent>( ent );
        modelHandle->size = vec2f{ 200.f, 200.f };

        auto textureHandle = engine.getEntityWorld().createComponent<CSpriteComponent>( ent );
        auto tex = CSprite( CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/player_sheet_orig.png" ) );
        tex.setFiltering( GL_NEAREST, GL_NEAREST );
        textureHandle->sprite = tex;


        auto animHandle = engine.getEntityWorld().createComponent<CAnimation2DComponent>( ent );
        animHandle->animSet.defaultAnimFrameIndex = 0;

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                // help a pixel offset to x and y for confident tex coords
                animHandle->animSet.vecKeyFrameClipRects.push_back( { x * 32.f + 0.5f, y * 32.f + 0.5f, 32.f, 32.f } ); 
            }
        }
        
        SAnimationData2D animation;

        animation.name = "walk_up";
        animation.framesPerSec = 2.f;
        animation.vecFrameIndices.clear();
        animation.vecFrameIndices.insert( animation.vecFrameIndices.end(), {0, 1, 2, 3, 4, 5, 6, 7} );
        animHandle->animSet.mapAnimNameToAnimData["walk_up"] = animation;

        animation.name = "walk_down";
        animation.framesPerSec = 4.f;
        animation.vecFrameIndices.clear();
        animation.vecFrameIndices.insert( animation.vecFrameIndices.end(), {8, 9, 10, 11, 12, 13, 14, 15} );
        animHandle->animSet.mapAnimNameToAnimData["walk_down"] = animation;

        animation.name = "walk_left";
        animation.framesPerSec = 8.f;
        animation.vecFrameIndices.clear();
        animation.vecFrameIndices.insert( animation.vecFrameIndices.end(), {16, 17, 18, 19, 20, 21, 22, 23} );
        animHandle->animSet.mapAnimNameToAnimData["walk_left"] = animation;

        animation.name = "walk_right";
        animation.framesPerSec = 16.f;
        animation.vecFrameIndices.clear();
        animation.vecFrameIndices.insert( animation.vecFrameIndices.end(), {24, 25, 26, 27, 28, 29, 30, 31} );
        animHandle->animSet.mapAnimNameToAnimData["walk_right"] = animation;



        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CAnimationDemoSystem::handleInput, this );
        l->setFilter( 
            []( const SDL_KeyboardEvent& e ) -> bool
            {
                return e.type == SDL_KEYDOWN;
            }
        );

        getEngine().getEventManager().registerListener(l);
        listenerGuard.reset( l, &getEngine().getEventManager() );
    }

    ~CAnimationDemoSystem()
    {
        getEngine().getEntityWorld().destroyEntity( ent );
    }

    void update( float dt ) override
    {

    }

    event_function handleInput( const SDL_KeyboardEvent& e )
    {
        auto animHandle = getEngine().getEntityWorld().getComponent<CAnimation2DComponent>( ent );

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

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CEngine engine( &window, 1.f / 60.f );

    engine.attachLogicSystem<CInputEventDispatchSystem>( SYSTEM_PRIORITY_HIGHEST );
    engine.attachLogicSystem<CCloseWindowListeningSystem>( SYSTEM_PRIORITY_HIGHEST + 1 );
    engine.attachLogicSystem<CSimple2DAnimationSystem>( SYSTEM_PRIORITY_HIGHEST + 2 );
    engine.attachLogicSystem<CAnimationDemoSystem>( SYSTEM_PRIORITY_HIGHEST + 3 );
    engine.attachRenderingSystem<CSimple2DRenderingSystem>( SYSTEM_PRIORITY_HIGHEST );

    showInfoMessageBox( testName,
        "left/right - change animation\n"
        "up/down - change playback speed\n"
        "space - pause/resume\n"
        "esc - stop\n"
    );

    engine.start();

    chestnutQuit();
    

    REQUIRE( showConfirmMessageBox( testName ) );
}
