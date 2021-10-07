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
            renderer.submitPolygon( poly1, body1.pos + body1.size / 2.f );
            renderer.submitPolygon( poly2, body2.pos + body2.size / 2.f );
            renderer.submitPolygon( poly3, body3.pos + body3.size / 2.f );
            renderer.submitPolygon( polyPoint, bodyPoint );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}


TEST_CASE( "Physics - point vs circle collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "Point vs circle collision" );

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


TEST_CASE( "Physics - circle vs circle collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "Circle vs circle collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 36 );
    SColliderBodyCircle2D circle1Body = { { 300.f, 300.f }, 150.f };
    ECollisionPolicyFlags circle1Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    SColliderBodyCircle2D circle2Body = { { 800.f, 300.f }, 50.f };
    ECollisionPolicyFlags circle2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D circle3 = colored_polygon_templates::coloredPolygonCircle( 100.f, 36 );
    SColliderBodyCircle2D circle3Body = { { 500.f, 600.f }, 100.f };
    ECollisionPolicyFlags circle3Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 100.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    SColliderBodyCircle2D circleUserBody = { { 0.f, 0.f }, 100.f };
    ECollisionPolicyFlags circleUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserBody.pos = vecCastType<float>( mousePos );


        if( resolveCircle2DVsCircle2D( circleUserBody, circleUserPolicy, circle1Body, circle1Policy ) )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsCircle2D( circleUserBody, circleUserPolicy, circle2Body, circle2Policy ) )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsCircle2D( circleUserBody, circleUserPolicy, circle3Body, circle3Policy ) )
        {
            circle3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Body.pos );
            renderer.submitPolygon( circle2, circle2Body.pos );
            renderer.submitPolygon( circle3, circle3Body.pos );
            renderer.submitPolygon( circleUser, circleUserBody.pos );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();   
}


TEST_CASE( "Physics - AABB vs AABB collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "AABB vs AABB collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );



    SColoredPolygon2D aabb1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    SColliderBodyAABB2D aabb1Body = { { 100.f, 150.f }, { 100.f, 200.f } };
    ECollisionPolicyFlags aabb1Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D aabb2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    SColliderBodyAABB2D aabb2Body = { { 500.f, 150.f }, { 100.f, 50.f } };
    ECollisionPolicyFlags aabb2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D aabb3 = colored_polygon_templates::coloredPolygonRectangle( 150.f, 150.f );
    SColliderBodyAABB2D aabb3Body = { { 900.f, 150.f }, { 150.f, 150.f } };
    ECollisionPolicyFlags aabb3Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabb4 = colored_polygon_templates::coloredPolygonRectangle( 300.f, 100.f );
    SColliderBodyAABB2D aabb4Body = { { 400.f, 500.f }, { 300.f, 100.f } };
    ECollisionPolicyFlags aabb4Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabbUser = colored_polygon_templates::coloredPolygonRectangle( 80.f, 120.f );
    aabbUser.color = { 0.f, 0.f, 1.f, 1.f };
    SColliderBodyAABB2D aabbUserBody = { { 0.f, 0.f }, { 80.f, 120.f } };
    ECollisionPolicyFlags aabbUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;



    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        aabbUserBody.pos = vecCastType<float>( mousePos );


        if( resolveAABB2DVsAABB2D( aabbUserBody, aabbUserPolicy, aabb1Body, aabb1Policy ) )
        {
            aabb1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserBody, aabbUserPolicy, aabb2Body, aabb2Policy ) )
        {
            aabb2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserBody, aabbUserPolicy, aabb3Body, aabb3Policy ) )
        {
            aabb3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserBody, aabbUserPolicy, aabb4Body, aabb4Policy ) )
        {
            aabb4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( aabb1, aabb1Body.pos + aabb1Body.size / 2.f );
            renderer.submitPolygon( aabb2, aabb2Body.pos + aabb2Body.size / 2.f );
            renderer.submitPolygon( aabb3, aabb3Body.pos + aabb3Body.size / 2.f );
            renderer.submitPolygon( aabb4, aabb4Body.pos + aabb4Body.size / 2.f );
            renderer.submitPolygon( aabbUser, aabbUserBody.pos  + aabbUserBody.size / 2.f );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();   
}


TEST_CASE( "Physics - Circle vs AABB collision", "[interactive]" )
{
    chestnutInit();

    auto window = createWindow( "Circle vs AABB collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );


    SColoredPolygon2D aabb1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    SColliderBodyAABB2D aabb1Body = { { 100.f, 150.f }, { 100.f, 200.f } };
    ECollisionPolicyFlags aabb1Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D aabb2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    SColliderBodyAABB2D aabb2Body = { { 500.f, 150.f }, { 100.f, 50.f } };
    ECollisionPolicyFlags aabb2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D aabb3 = colored_polygon_templates::coloredPolygonRectangle( 150.f, 150.f );
    SColliderBodyAABB2D aabb3Body = { { 900.f, 150.f }, { 150.f, 150.f } };
    ECollisionPolicyFlags aabb3Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabb4 = colored_polygon_templates::coloredPolygonRectangle( 300.f, 100.f );
    SColliderBodyAABB2D aabb4Body = { { 400.f, 500.f }, { 300.f, 100.f } };
    ECollisionPolicyFlags aabb4Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    SColliderBodyCircle2D circleUserBody = { { 0.f, 0.f }, 50.f };
    ECollisionPolicyFlags circleUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserBody.pos = vecCastType<float>( mousePos );


        if( resolveCircle2DVsAABB2D( circleUserBody, circleUserPolicy, aabb1Body, aabb1Policy ) )
        {
            aabb1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserBody, circleUserPolicy, aabb2Body, aabb2Policy ) )
        {
            aabb2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserBody, circleUserPolicy, aabb3Body, aabb3Policy ) )
        {
            aabb3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserBody, circleUserPolicy, aabb4Body, aabb4Policy ) )
        {
            aabb4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( aabb1, aabb1Body.pos + aabb1Body.size / 2.f );
            renderer.submitPolygon( aabb2, aabb2Body.pos + aabb2Body.size / 2.f );
            renderer.submitPolygon( aabb3, aabb3Body.pos + aabb3Body.size / 2.f );
            renderer.submitPolygon( aabb4, aabb4Body.pos + aabb4Body.size / 2.f );
            renderer.submitPolygon( circleUser, circleUserBody.pos );
            renderer.render();
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}