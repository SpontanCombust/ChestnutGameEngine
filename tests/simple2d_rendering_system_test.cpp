#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/ecs_impl/event_listener_guard.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "../src/chestnut/engine/ecs_impl/components/texture2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"

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

class CSpriteSteeringSystem : public ISystem
{
private:
    CEventListenerGuard inputListenerGuard;

    ecs::entityid_t player;
    vec2f sizeDelta;
    vec2f posDelta;
    vec2f scaleDelta;
    float rotDelta;
    ETexture2DToModel2DAdjust texAdjust;

public:
    CSpriteSteeringSystem( CEngine& engine ) : ISystem( engine )
    {
        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CSpriteSteeringSystem::handleInput, this );
        getEngine().getEventManager().registerListener(l);

        inputListenerGuard.reset( l, &getEngine().getEventManager() );

        player = getEngine().getEntityWorld().createEntity();
        getEngine().getEntityWorld().createComponent<CTransform2DComponent>( player );

        auto modelHandle = getEngine().getEntityWorld().createComponent<CModel2DComponent>( player );
        modelHandle->size = { 100.f, 100.f };

        auto textureHandle = getEngine().getEntityWorld().createComponent<CTexture2DComponent>( player );
        REQUIRE_NOTHROW( textureHandle->texture = CTexture2D( loadTexture2DResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/awesomeface.png" ) ) );
    }

    ~CSpriteSteeringSystem()
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
                rotDelta = 0.5f;
                break;
            case SDLK_e:
                rotDelta = -0.5f;
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


TEST_CASE( "Systems - Simple2D rendering system test - general", "[manual][demo]" )
{
    const char *testName = "Simple2D rendering system test - general";

    chestnutInit();

    CWindow window( testName, 1000 );
    REQUIRE( window.isValid() );

    CEngine engine( &window, 1.f / 60.f );

    engine.attachLogicSystem<CInputEventDispatchSystem>( SYSTEM_PRIORITY_HIGHEST );
    engine.attachLogicSystem<CCloseWindowListeningSystem>( SYSTEM_PRIORITY_HIGHEST + 1 );
    engine.attachLogicSystem<CSpriteSteeringSystem>( SYSTEM_PRIORITY_HIGHEST + 2 );
    engine.attachRenderingSystem<CSimple2DRenderingSystem>( SYSTEM_PRIORITY_HIGHEST );

    showInfoMessageBox( testName,
        "UP-DOWN-LEFT-RIGHT - change transformation position\n"
        "W-A-S-D - change transformation scale\n"
        "Q-E - change transformation rotation\n"
        "I-J-K-L - change model size\n"
        "F - change texture to model adjust type"
    );

    engine.start();

    chestnutQuit();


    REQUIRE( showConfirmMessageBox( testName ) );
}






const char *orderToString( EDefaultRenderOrder order )
{
    switch( order )
    {
    case EDefaultRenderOrder::BOTTOM_TO_TOP:
        return "BOTTOM_TO_TOP";
    case EDefaultRenderOrder::TOP_TO_BOTTOM:
        return "TOP_TO_BOTTOM";
    case EDefaultRenderOrder::LEFT_TO_RIGHT:
        return "LEFT_TO_RIGHT";
    default:
        return "RIGHT_TO_LEFT";
    }
}

class COrderingDemonstationSystem : public ISystem
{
public:
    std::vector< ecs::entityid_t > ents;
    EDefaultRenderOrder order;
    CEventListenerGuard listenerGuard;

    COrderingDemonstationSystem( CEngine& engine ) : ISystem( engine ) 
    {
        auto tex = loadTexture2DResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/awesomeface.png" );
        
        ecs::CComponentHandle< CTransform2DComponent > transform;
        ecs::CComponentHandle< CTexture2DComponent > texture;
        ecs::CComponentHandle< CModel2DComponent > model;

        const float w = (float)getEngine().getWindow().getSizeWidth();
        const float h = (float)getEngine().getWindow().getSizeHeight();

        ents = getEngine().getEntityWorld().createEntities(9);
        for( ecs::entityid_t ent : ents )
        {
            getEngine().getEntityWorld().createComponent<CTransform2DComponent>( ent );
            model = getEngine().getEntityWorld().createComponent<CModel2DComponent>( ent );
            model->size = { 100.f, 100.f };
            texture = getEngine().getEntityWorld().createComponent<CTexture2DComponent>( ent );
            texture->texture = CTexture2D( tex );
        }

        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[0] );
        transform->position = vec2f{ w / 2, h / 2 };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[1] );
        transform->position = vec2f{ w / 2, h / 2 - 75.f };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[2] );
        transform->position = vec2f{ w / 2, h / 2 - 150.f };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[3] );
        transform->position = vec2f{ w / 2, h / 2 + 75.f };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[4] );
        transform->position = vec2f{ w / 2, h / 2 + 150.f };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[5] );
        transform->position = vec2f{ w / 2 - 75.f, h / 2 };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[6] );
        transform->position = vec2f{ w / 2 - 150.f, h / 2 };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[7] );
        transform->position = vec2f{ w / 2 + 75.f, h / 2 };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[8] );
        transform->position = vec2f{ w / 2 + 150.f, h / 2 };

        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &COrderingDemonstationSystem::handleInput, this );
        l->setFilter( []( const SDL_KeyboardEvent& e ) 
        {
            return e.type == SDL_KEYDOWN && e.keysym.sym == SDLK_f;
        });
        getEngine().getEventManager().registerListener(l);
        listenerGuard.reset( l, &getEngine().getEventManager() );

        order = EDefaultRenderOrder::BOTTOM_TO_TOP;
    }

    ~COrderingDemonstationSystem()
    {
        getEngine().getEntityWorld().destroyEntities( ents );
    }

    void update( float dt ) override
    {

    }

    event_function handleInput( const SDL_KeyboardEvent& e )
    {
        switch( order )
        {
        case EDefaultRenderOrder::BOTTOM_TO_TOP:
            order = EDefaultRenderOrder::TOP_TO_BOTTOM;
            break;
        case EDefaultRenderOrder::TOP_TO_BOTTOM:
            order = EDefaultRenderOrder::LEFT_TO_RIGHT;
            break;
        case EDefaultRenderOrder::LEFT_TO_RIGHT:
            order = EDefaultRenderOrder::RIGHT_TO_LEFT;
            break;
        default:
            order = EDefaultRenderOrder::BOTTOM_TO_TOP;
        }
        
        CSimple2DRenderingSystem *system = getEngine().getSystem<CSimple2DRenderingSystem>();
        if( system ) 
        {
            system->setDefaultRenderOrder( order );
        }

        std::string s = "Ordering type: ";
        s += orderToString( order );
        getEngine().getWindow().setTitle( s.c_str() );
    }
};


TEST_CASE( "Systems - Simple2D rendering system test - default ordering", "[manual][demo]" )
{
    const char *testName = "Simple2D rendering system test - default ordering";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CEngine engine( &window, 1.f / 60.f );

    engine.attachLogicSystem<CInputEventDispatchSystem>( SYSTEM_PRIORITY_HIGHEST );
    engine.attachLogicSystem<CCloseWindowListeningSystem>( SYSTEM_PRIORITY_HIGHEST + 1 );
    engine.attachLogicSystem<COrderingDemonstationSystem>( SYSTEM_PRIORITY_HIGHEST + 2 );
    engine.attachRenderingSystem<CSimple2DRenderingSystem>( SYSTEM_PRIORITY_HIGHEST );

    showInfoMessageBox( testName,
        "F - switch ordering type"
    );

    engine.start();

    chestnutQuit();


    REQUIRE( showConfirmMessageBox( testName ) );
}





class CLayeringDemonstrationSystem : public ISystem
{
public:
    std::vector< ecs::entityid_t > ents;
    CEventListenerGuard listenerGuard;

    CLayeringDemonstrationSystem( CEngine& engine ) : ISystem( engine )
    {
        auto tex = loadTexture2DResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/awesomeface.png" );
        
        ecs::CComponentHandle< CTransform2DComponent > transform;
        ecs::CComponentHandle< CTexture2DComponent > texture;
        ecs::CComponentHandle< CModel2DComponent > model;
        ecs::CComponentHandle< CRenderLayerComponent > layer;

        const float w = (float)getEngine().getWindow().getSizeWidth();
        const float h = (float)getEngine().getWindow().getSizeHeight();

        ents = getEngine().getEntityWorld().createEntities(3);
        for( ecs::entityid_t ent : ents )
        {
            getEngine().getEntityWorld().createComponent<CTransform2DComponent>( ent );
            model = getEngine().getEntityWorld().createComponent<CModel2DComponent>( ent );
            model->size = { 100.f, 100.f };
            texture = getEngine().getEntityWorld().createComponent<CTexture2DComponent>( ent );
            texture->texture = CTexture2D( tex );
            getEngine().getEntityWorld().createComponent<CRenderLayerComponent>( ent ); // should default to layer 0
        }  

        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[0] );
        transform->position = vec2f{ w / 2 - 75.f, h / 2 }; 
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[1] );
        transform->position = vec2f{ w / 2, h / 2 };
        transform = getEngine().getEntityWorld().getComponent<CTransform2DComponent>( ents[2] );
        transform->position = vec2f{ w / 2 + 75.f, h / 2 }; 


        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CLayeringDemonstrationSystem::handleInput, this );
        l->setFilter( []( const SDL_KeyboardEvent& e ) 
        {
            return e.type == SDL_KEYDOWN;
        });
        getEngine().getEventManager().registerListener(l);
        listenerGuard.reset( l, &getEngine().getEventManager() );
    }

    ~CLayeringDemonstrationSystem()
    {
        getEngine().getEntityWorld().destroyEntities( ents );
    }

    void update( float dt ) override
    {

    }

    event_function handleInput( const SDL_KeyboardEvent& e )
    {
        ecs::CComponentHandle<CRenderLayerComponent> handle;

        switch( e.keysym.sym )
        {
        case SDLK_q:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[0] );
            handle->layer++;
            break;
        case SDLK_a:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[0] );
            handle->layer--;
            break;
        case SDLK_w:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[1] );
            handle->layer++;
            break;
        case SDLK_s:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[1] );
            handle->layer--;
            break;
        case SDLK_e:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[2] );
            handle->layer++;
            break;
        case SDLK_d:
            handle = getEngine().getEntityWorld().getComponent<CRenderLayerComponent>( ents[2] );
            handle->layer--;
            break;
        }
    }
};

TEST_CASE( "Systems - Simple2D rendering system test - layering", "[manual][demo]" )
{
    const char *testName = "Simple2D rendering system test - layering";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CEngine engine( &window, 1.f / 60.f );

    engine.attachLogicSystem<CInputEventDispatchSystem>( SYSTEM_PRIORITY_HIGHEST );
    engine.attachLogicSystem<CCloseWindowListeningSystem>( SYSTEM_PRIORITY_HIGHEST + 1 );
    engine.attachLogicSystem<CLayeringDemonstrationSystem>( SYSTEM_PRIORITY_HIGHEST + 2 );
    engine.attachRenderingSystem<CSimple2DRenderingSystem>( SYSTEM_PRIORITY_HIGHEST );

    showInfoMessageBox( testName,
        "Q/A - raise/lower object 1 layer\n"
        "W/S - raise/lower object 2 layer\n"
        "E/D - raise/lower object 3 layer\n"
    );

    engine.start();

    chestnutQuit();
    

    REQUIRE( showConfirmMessageBox( testName ) );
}