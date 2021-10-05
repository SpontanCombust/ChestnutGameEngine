#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/physics/collider.hpp"
#include "../src/chestnut/engine/physics/collision_resolution.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"

#include <SDL2/SDL_events.h>


using namespace chestnut::engine;

TEST_CASE( "Physics - point vs AABB collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "Point vs AABB collision" );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D poly1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 300.f );
    SColliderBodyAABB2D body1 = { { 50.f, 50.f }, { 100.f, 300.f } };
    ECollisionPolicyFlags policy1 = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D poly2 = colored_polygon_templates::coloredPolygonSquare( 50.f );
    SColliderBodyAABB2D body2 = { { 400.f, 500.f }, { 50.f, 50.f } };
    ECollisionPolicyFlags policy2 = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D poly3 = colored_polygon_templates::coloredPolygonRectangle( 200.f, 100.f );
    SColliderBodyAABB2D body3 = { { 300.f, 200.f }, { 200.f, 100.f } };
    ECollisionPolicyFlags policy3 = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D polyPoint = colored_polygon_templates::coloredPolygonSquare( 4.f );
    polyPoint.color = { 0.f, 0.f, 1.f, 1.f };
    SColliderBodyPoint2D bodyPoint = { 0.f, 0.f };
    ECollisionPolicyFlags policyPoint = ECollisionPolicyFlags::AFFECTED;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        bodyPoint = vecCastType<float>( mousePos );


        if( resolvePoint2DVsAABB2D( bodyPoint, policyPoint, body1, policy1 ) )
        {
            poly1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            poly1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsAABB2D( bodyPoint, policyPoint, body2, policy2 ) )
        {
            poly2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            poly2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsAABB2D( bodyPoint, policyPoint, body3, policy3 ) )
        {
            poly3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            poly3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( poly1, body1.pos + vec2f{ 50.f, 150.f } );
            renderer.submitPolygon( poly2, body2.pos + vec2f{ 25.f, 25.f } );
            renderer.submitPolygon( poly3, body3.pos + vec2f{ 100.f, 50.f } );
            renderer.submitPolygon( polyPoint, bodyPoint );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}


TEST_CASE( "Physics - point vs circle collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "Point vs AABB collision" );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 24 );
    SColliderBodyCircle2D circle1Body = { { 200.f, 200.f }, 150.f };
    ECollisionPolicyFlags circle1Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 12 );
    SColliderBodyCircle2D circle2Body = { { 500.f, 200.f }, 50.f };
    ECollisionPolicyFlags circle2Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D point = colored_polygon_templates::coloredPolygonSquare( 4.f );
    point.color = { 0.f, 0.f, 1.f, 1.f };
    SColliderBodyPoint2D pointBody = { 0.f, 0.f };
    ECollisionPolicyFlags pointPolicy = ECollisionPolicyFlags::AFFECTED;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        pointBody = vecCastType<float>( mousePos );


        if( resolvePoint2DVsCircle2D( pointBody, pointPolicy, circle1Body, circle1Policy ) )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsCircle2D( pointBody, pointPolicy, circle2Body, circle2Policy ) )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Body.pos );
            renderer.submitPolygon( circle2, circle2Body.pos );
            renderer.submitPolygon( point, pointBody );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}