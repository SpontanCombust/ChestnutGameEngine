#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener_guard.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "../src/chestnut/engine/ecs_impl/components/texture2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include "system_test_utils.hpp"
#include "test_utils.hpp"


using namespace chestnut;
using namespace chestnut::engine;

const char *adjustToString( ETexture2DToModel2DAdjust adjust )
{
    switch( adjust )
    {
    case ETexture2DToModel2DAdjust::NONE: return "NONE";
    case ETexture2DToModel2DAdjust::SCALED: return "SCALED";
    case ETexture2DToModel2DAdjust::SPANNED: return "SPANNED";
    case ETexture2DToModel2DAdjust::ZOOMED: return "ZOOMED";
    default: return "";
    }
}

class CSteeringSystem : public ISystem
{
private:
    CEventListenerGuard inputListenerGuard;

    ecs::entityid player;
    vec2f sizeDelta;
    vec2f posDelta;
    vec2f scaleDelta;
    float rotDelta;
    ETexture2DToModel2DAdjust texAdjust;

public:
    CSteeringSystem( CEngine& engine ) : ISystem( engine )
    {
        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CSteeringSystem::handleInput, this );
        getEngine().getEventManager().registerListener(l);

        inputListenerGuard.reset( l, &getEngine().getEventManager() );

        player = getEngine().getEntityWorld().createEntity();
        getEngine().getEntityWorld().createComponent<CTransform2DComponent>( player );

        auto modelHandle = getEngine().getEntityWorld().createComponent<CModel2DComponent>( player );
        modelHandle->size = { 100.f, 100.f };

        auto textureHandle = getEngine().getEntityWorld().createComponent<CTexture2DComponent>( player );
        REQUIRE_NOTHROW( textureHandle->texture = CTexture2D( loadTexture2DResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/awesomeface.png" ) ) );
    }

    ~CSteeringSystem()
    {
        getEngine().getEntityWorld().destroyEntity( player );
    }

    void update( float dt ) override
    {
        auto modelHandle = getEngine().getEntityWorld().getComponent<CModel2DComponent>( player );
        modelHandle->size += sizeDelta * dt;

        auto transformHandle = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( player );
        transformHandle->position += posDelta * dt;
        transformHandle->scale += scaleDelta * dt;
        transformHandle->rotation += rotDelta * dt;

        auto textureHandle = getEngine().getEntityWorld().getComponent<CTexture2DComponent>( player );
        textureHandle->adjust = texAdjust;


        getEngine().getWindow().setTitle(
            "FPS=" + std::to_string( getEngine().getGameUpdatesPerSecond() ) +
            ", Pos=" + vecToString( transformHandle->position ) +
            ", Scale=" + vecToString( transformHandle->scale ) +
            ", Rot=" + std::to_string( transformHandle->rotation ) +
            ", Model=" + vecToString( modelHandle->size ) +
            ", Adjust=" + adjustToString( textureHandle->adjust )
        );
    }

    event_function handleInput( const SDL_KeyboardEvent& e )
    {
        if( e.type == SDL_KEYDOWN )
        {
            switch( e.keysym.sym )
            {
            case SDLK_UP:
                posDelta.y = -100.f;
                break;
            case SDLK_DOWN:
                posDelta.y = 100.f;
                break;
            case SDLK_LEFT:
                posDelta.x = -100.f;
                break;
            case SDLK_RIGHT:
                posDelta.x = 100.f;
                break;
            case SDLK_w:
                scaleDelta.y = 0.5f;
                break;
            case SDLK_s:
                scaleDelta.y = -0.5f;
                break;
            case SDLK_a:
                scaleDelta.x = -0.5f;
                break;
            case SDLK_d:
                scaleDelta.x = 0.5f;
                break;
            case SDLK_q:
                rotDelta = -0.5f;
                break;
            case SDLK_e:
                rotDelta = 0.5f;
                break;
            case SDLK_j:
                sizeDelta.x = -100.f;
                break;
            case SDLK_l:
                sizeDelta.x = 100.f;
                break;
            case SDLK_k:
                sizeDelta.y = -100.f;
                break;
            case SDLK_i:
                sizeDelta.y = 100.f;
                break;
            case SDLK_f:
                if( texAdjust == ETexture2DToModel2DAdjust::NONE )
                    texAdjust = ETexture2DToModel2DAdjust::SCALED;
                else if( texAdjust == ETexture2DToModel2DAdjust::SCALED )
                    texAdjust = ETexture2DToModel2DAdjust::SPANNED;
                else if( texAdjust == ETexture2DToModel2DAdjust::SPANNED )
                    texAdjust = ETexture2DToModel2DAdjust::ZOOMED;
                else
                    texAdjust = ETexture2DToModel2DAdjust::NONE;
                break;
            }
        }
        else
        {
            switch( e.keysym.sym )
            {
            case SDLK_UP:
            case SDLK_DOWN:
                posDelta.y = 0.f;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                posDelta.x = 0.f;
                break;
            case SDLK_w:
            case SDLK_s:
                scaleDelta.y = 0.f;
                break;
            case SDLK_a:
            case SDLK_d:
                scaleDelta.x = 0.f;
                break;
            case SDLK_q:
            case SDLK_e:
                rotDelta = 0.f;
                break;
            case SDLK_j:
            case SDLK_l:
                sizeDelta.x = 0.f;
                break;
            case SDLK_k:
            case SDLK_i:
                sizeDelta.y = 0.f;
                break;
            }
        }
    }
};


TEST_CASE( "Systems - Simple2D rendering system test", "[interactive][demo]" )
{
    chestnutInit();

    CWindow window( "Simple2D rendering system test", 1000 );
    REQUIRE( window.isValid() );

    CEngine engine( &window, 1.f / 60.f );

    engine.attachLogicSystem<CInputEventDispatchSystem>( SYSTEM_PRIORITY_HIGHEST );
    engine.attachLogicSystem<CCloseWindowListeningSystem>( SYSTEM_PRIORITY_HIGHEST + 1 );
    engine.attachLogicSystem<CSteeringSystem>( SYSTEM_PRIORITY_HIGHEST + 2 );
    engine.attachRenderingSystem<CSimple2DRenderingSystem>( SYSTEM_PRIORITY_HIGHEST );

    showInfoMessageBox( "Systems - Simple2D rendering system test",
        "UP-DOWN-LEFT-RIGHT - change transformation position\n"
        "W-A-S-D - change transformation scale\n"
        "Q-E - change transformation rotation\n"
        "I-J-K-L - change model size\n"
        "F - change texture to model adjust type"
    );

    engine.start();


    chestnutQuit();
}
