#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/input_event_dispatch_system.hpp"
#include "../src/chestnut/engine/ecs_impl/systems/simple2d_rendering_system.hpp"
#include "../src/chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "../src/chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"

#include "test_utils.hpp"

#include <SDL_events.h>


using namespace chestnut;
using namespace chestnut::engine;

const char *adjustToString( ESpriteToModel2DAdjust adjust )
{
    switch( adjust )
    {
    case ESpriteToModel2DAdjust::NONE: return "NONE";
    case ESpriteToModel2DAdjust::SCALED: return "SCALED";
    case ESpriteToModel2DAdjust::SPANNED: return "SPANNED";
    case ESpriteToModel2DAdjust::ZOOMED: return "ZOOMED";
    default: return "";
    }
}

class CSpriteSteeringSystem : public ILogicSystem
{
private:
    ecs::entityid_t player;
    vec2f sizeDelta;
    vec2f posDelta;
    vec2f scaleDelta;
    float rotDelta = 0.f;
    ESpriteToModel2DAdjust texAdjust = ESpriteToModel2DAdjust::NONE;

public:
    CSpriteSteeringSystem(systempriority_t prio) : ILogicSystem(prio)
    {
        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CSpriteSteeringSystem::handleInput, this );
        addEventListener("handleInput", l);

        player = CEngine::getInstance().getEntityWorld().createEntity();
        CEngine::getInstance().getEntityWorld().createComponent<CTransform2DComponent>( player );

        auto modelHandle = CEngine::getInstance().getEntityWorld().createComponent<CModel2DComponent>( player );
        modelHandle->size = { 100.f, 100.f };

        auto spriteHandle = CEngine::getInstance().getEntityWorld().createComponent<CSpriteComponent>( player );
        REQUIRE_NOTHROW( spriteHandle->sprite = CSprite( CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/awesomeface.png" ).value() ) );
    }

    ~CSpriteSteeringSystem()
    {
        CEngine::getInstance().getEntityWorld().destroyEntity( player );
    }

    void update( float dt ) override
    {
        auto modelHandle = CEngine::getInstance().getEntityWorld().getComponent<CModel2DComponent>( player );
        modelHandle->size += sizeDelta * dt;

        auto transformHandle = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( player );
        transformHandle->position += posDelta * dt;
        transformHandle->scale += scaleDelta * dt;
        transformHandle->rotation += rotDelta * dt;

        auto spriteHandle = CEngine::getInstance().getEntityWorld().getComponent<CSpriteComponent>( player );
        spriteHandle->adjust = texAdjust;


        CEngine::getInstance().getWindow().setTitle(
            "FPS=" + std::to_string( CEngine::getInstance().getGameUpdatesPerSecond() ) +
            ", Pos=" + vecToString( transformHandle->position ) +
            ", Scale=" + vecToString( transformHandle->scale ) +
            ", Rot=" + std::to_string( transformHandle->rotation ) +
            ", Model=" + vecToString( modelHandle->size ) +
            ", Adjust=" + adjustToString( spriteHandle->adjust )
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
                if( texAdjust == ESpriteToModel2DAdjust::NONE )
                    texAdjust = ESpriteToModel2DAdjust::SCALED;
                else if( texAdjust == ESpriteToModel2DAdjust::SCALED )
                    texAdjust = ESpriteToModel2DAdjust::SPANNED;
                else if( texAdjust == ESpriteToModel2DAdjust::SPANNED )
                    texAdjust = ESpriteToModel2DAdjust::ZOOMED;
                else
                    texAdjust = ESpriteToModel2DAdjust::NONE;
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

    CEngine::createInstance( window, 1.f / 60.f );

    CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
    CEngine::getInstance().attachSystem( new CSpriteSteeringSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
    CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );

    showInfoMessageBox( testName,
        "UP-DOWN-LEFT-RIGHT - change transformation position\n"
        "W-A-S-D - change transformation scale\n"
        "Q-E - change transformation rotation\n"
        "I-J-K-L - change model size\n"
        "F - change sprite to model adjust type"
    );

    CEngine::getInstance().start();

    CEngine::deleteInstance();
    chestnutQuit();
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

class COrderingDemonstationSystem : public ILogicSystem
{
public:
    std::vector< ecs::entityid_t > ents;
    EDefaultRenderOrder order;

    COrderingDemonstationSystem(systempriority_t prio) : ILogicSystem(prio) 
    {
        std::shared_ptr<CTexture2DResource> tex;
        REQUIRE_NOTHROW(tex = CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/awesomeface.png" ).value() );
        
        ecs::CComponentHandle< CTransform2DComponent > transform;
        ecs::CComponentHandle< CSpriteComponent > sprite;
        ecs::CComponentHandle< CModel2DComponent > model;

        const vec2f size = vecCastType<float>(CEngine::getInstance().getWindow().getSize());

        for(int i = 0; i < 9; i++)
        {
            ecs::entityid_t ent = CEngine::getInstance().getEntityWorld().createEntity();
            this->ents.push_back(ent);

            CEngine::getInstance().getEntityWorld().createComponent<CTransform2DComponent>( ent );
            model = CEngine::getInstance().getEntityWorld().createComponent<CModel2DComponent>( ent );
            model->size = { 100.f, 100.f };
            sprite = CEngine::getInstance().getEntityWorld().createComponent<CSpriteComponent>( ent );
            sprite->sprite = CSprite( tex );
        }

        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[0] );
        transform->position = vec2f{ size.x / 2, size.y / 2 };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[1] );
        transform->position = vec2f{ size.x / 2, size.y / 2 - 75.f };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[2] );
        transform->position = vec2f{ size.x / 2, size.y / 2 - 150.f };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[3] );
        transform->position = vec2f{ size.x / 2, size.y / 2 + 75.f };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[4] );
        transform->position = vec2f{ size.x / 2, size.y / 2 + 150.f };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[5] );
        transform->position = vec2f{ size.x / 2 - 75.f, size.y / 2 };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[6] );
        transform->position = vec2f{ size.x / 2 - 150.f, size.y / 2 };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[7] );
        transform->position = vec2f{ size.x / 2 + 75.f, size.y / 2 };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[8] );
        transform->position = vec2f{ size.x / 2 + 150.f, size.y / 2 };

        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &COrderingDemonstationSystem::handleInput, this );
        l->setFilter( []( const SDL_KeyboardEvent& e ) 
        {
            return e.type == SDL_KEYDOWN && e.keysym.sym == SDLK_f;
        });
        addEventListener("handleInput", l);

        order = EDefaultRenderOrder::BOTTOM_TO_TOP;
    }

    ~COrderingDemonstationSystem()
    {
        for(ecs::entityid_t ent : this->ents)
        {
            CEngine::getInstance().getEntityWorld().destroyEntity( ent );
        }
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
        
        CSimple2DRenderingSystem *system = CEngine::getInstance().getRenderingSystem<CSimple2DRenderingSystem>();
        if( system ) 
        {
            system->setDefaultRenderOrder( order );
        }

        std::string s = "Ordering type: ";
        s += orderToString( order );
        CEngine::getInstance().getWindow().setTitle( s.c_str() );
    }
};


TEST_CASE( "Systems - Simple2D rendering system test - default ordering", "[manual][demo]" )
{
    const char *testName = "Simple2D rendering system test - default ordering";

    chestnutInit();

    CWindow window( testName );

    CEngine::createInstance( window, 1.f / 60.f );

    CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
    CEngine::getInstance().attachSystem( new COrderingDemonstationSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
    CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );

    showInfoMessageBox( testName,
        "F - switch ordering type"
    );

    CEngine::getInstance().start();

    CEngine::deleteInstance();
    chestnutQuit();
}





class CLayeringDemonstrationSystem : public ILogicSystem
{
public:
    std::vector< ecs::entityid_t > ents;

    CLayeringDemonstrationSystem(systempriority_t prio) : ILogicSystem(prio)
    {
        std::shared_ptr<CTexture2DResource> tex;
        REQUIRE_NOTHROW( tex = CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/awesomeface.png" ).value() );
        
        ecs::CComponentHandle< CTransform2DComponent > transform;
        ecs::CComponentHandle< CSpriteComponent > sprite;
        ecs::CComponentHandle< CModel2DComponent > model;
        ecs::CComponentHandle< CRenderLayerComponent > layer;

        const vec2f size = vecCastType<float>(CEngine::getInstance().getWindow().getSize());

        for(int i = 0; i < 3; i++)
        {
            ecs::entityid_t ent = CEngine::getInstance().getEntityWorld().createEntity();
            this->ents.push_back(ent);

            CEngine::getInstance().getEntityWorld().createComponent<CTransform2DComponent>( ent );
            model = CEngine::getInstance().getEntityWorld().createComponent<CModel2DComponent>( ent );
            model->size = { 100.f, 100.f };
            sprite = CEngine::getInstance().getEntityWorld().createComponent<CSpriteComponent>( ent );
            sprite->sprite = CSprite( tex );
            CEngine::getInstance().getEntityWorld().createComponent<CRenderLayerComponent>( ent ); // should default to layer 0
        }  

        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[0] );
        transform->position = vec2f{ size.x / 2 - 75.f, size.y / 2 }; 
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[1] );
        transform->position = vec2f{ size.x / 2, size.y / 2 };
        transform = CEngine::getInstance().getEntityWorld().getComponent<CTransform2DComponent>( ents[2] );
        transform->position = vec2f{ size.x / 2 + 75.f, size.y / 2 }; 


        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CLayeringDemonstrationSystem::handleInput, this );
        l->setFilter( []( const SDL_KeyboardEvent& e ) 
        {
            return e.type == SDL_KEYDOWN;
        });
        addEventListener("handleInput", l);
    }

    ~CLayeringDemonstrationSystem()
    {
        for(ecs::entityid_t ent : this->ents)
        {
            CEngine::getInstance().getEntityWorld().destroyEntity( ent );
        }
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
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[0] );
            handle->layer++;
            break;
        case SDLK_a:
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[0] );
            handle->layer--;
            break;
        case SDLK_w:
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[1] );
            handle->layer++;
            break;
        case SDLK_s:
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[1] );
            handle->layer--;
            break;
        case SDLK_e:
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[2] );
            handle->layer++;
            break;
        case SDLK_d:
            handle = CEngine::getInstance().getEntityWorld().getComponent<CRenderLayerComponent>( ents[2] );
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

    CEngine::createInstance( window, 1.f / 60.f );

    CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
    CEngine::getInstance().attachSystem( new CLayeringDemonstrationSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
    CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );

    showInfoMessageBox( testName,
        "Q/A - raise/lower object 1 layer\n"
        "W/S - raise/lower object 2 layer\n"
        "E/D - raise/lower object 3 layer\n"
    );

    CEngine::getInstance().start();

    CEngine::deleteInstance();
    chestnutQuit();
}






class CCameraDemonstrationSystem : public ILogicSystem
{
public:
    ecs::entityid_t ent;

    vec2f posDelta;
    vec2f dimDelta;
    float zoomDelta = 0.f;

    CCameraDemonstrationSystem(systempriority_t prio) : ILogicSystem(prio)
    {
        std::shared_ptr<CTexture2DResource> tex;
        REQUIRE_NOTHROW( tex = CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/awesomeface.png" ).value() );
        
        ecs::CComponentHandle< CTransform2DComponent > transform;
        ecs::CComponentHandle< CSpriteComponent > sprite;
        ecs::CComponentHandle< CModel2DComponent > model;


        auto& engine = CEngine::getInstance();

        ent = engine.getEntityWorld().createEntity();

        transform = engine.getEntityWorld().createComponent<CTransform2DComponent>( ent );
        model = engine.getEntityWorld().createComponent<CModel2DComponent>( ent );
        model->size = { 100.f, 100.f };
        sprite = engine.getEntityWorld().createComponent<CSpriteComponent>( ent );
        sprite->sprite = CSprite( tex );


        auto l = new CEventListener<SDL_KeyboardEvent>();
        l->setHandler( &CCameraDemonstrationSystem::handleInput, this );
        addEventListener("handleInput", l);
    }

    ~CCameraDemonstrationSystem()
    {
        CEngine::getInstance().getEntityWorld().destroyEntity( ent );
    }

    void update( float dt ) override
    {
        CSimple2DRenderingSystem *sys = CEngine::getInstance().getRenderingSystem<CSimple2DRenderingSystem>();

        if( sys )
        {
            CCamera2D& camera = sys->getCamera();

            camera.m_position += posDelta * dt;
            camera.m_dimensions += dimDelta * dt;
            camera.m_zoom += zoomDelta * dt;
        }
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
                dimDelta.y = 100.f;
                break;
            case SDLK_s:
                dimDelta.y = -100.f;
                break;
            case SDLK_a:
                dimDelta.x = -100.f;
                break;
            case SDLK_d:
                dimDelta.x = 100.f;
                break;
            case SDLK_q:
                zoomDelta = -0.5f;
                break;
            case SDLK_e:
                zoomDelta = 0.5f;
                break;
            }
        }
        else if( e.type == SDL_KEYUP )
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
                dimDelta.y = 0.f;
                break;
            case SDLK_a:
            case SDLK_d:
                dimDelta.x = 0.f;
                break;
            case SDLK_q:
            case SDLK_e:
                zoomDelta = 0.f;
                break;
            }
        }
    }
};

TEST_CASE( "Systems - Simple2D rendering system test - camera", "[manual][demo]" )
{
    const char *testName = "Simple2D rendering system test - camera";

    chestnutInit();

    CWindow window( testName );

    CEngine::createInstance( window, 1.f / 60.f );

    CEngine::getInstance().attachSystem( new CInputEventDispatchSystem(SYSTEM_PRIORITY_HIGHEST) );
    CEngine::getInstance().attachSystem( new CCameraDemonstrationSystem(SYSTEM_PRIORITY_HIGHEST + 2) );
    CEngine::getInstance().attachSystem( new CSimple2DRenderingSystem(SYSTEM_PRIORITY_HIGHEST) );

    showInfoMessageBox( testName,
        "UP/DOWN/LEFT/RIGHT - move camera\n"
        "S/W - make view smaller/bigger in y axis\n"
        "A/D - make view smaller/bigger in x axis\n"
        "Q/E - zoom out/in\n"
    );

    CEngine::getInstance().start();

    CEngine::deleteInstance();
    chestnutQuit();
}