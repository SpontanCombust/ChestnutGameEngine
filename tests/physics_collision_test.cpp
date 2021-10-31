#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/physics/collider.hpp"
#include "../src/chestnut/engine/physics/collision_resolution.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include <SDL2/SDL_events.h>


using namespace chestnut::engine;

TEST_CASE( "Physics - point vs AABB collision", "[interactive][demo]" )
{
    chestnutInit();

    auto window = createWindow( "Point vs AABB collision" );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D aabb1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 300.f );
    vec2f aabb1Pos { 100.f, 250.f };
    SColliderBodyAABB2D aabb1Body { { 100.f, 300.f } };
    ECollisionPolicyFlags aabb1Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D aabb2 = colored_polygon_templates::coloredPolygonRectangle( 200.f, 100.f );
    vec2f aabb2Pos { 400.f, 250.f };
    SColliderBodyAABB2D aabb2Body = { { 200.f, 100.f } };
    ECollisionPolicyFlags aabb2Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabb3 = colored_polygon_templates::coloredPolygonSquare( 50.f );
    vec2f aabb3Pos { 400.f, 500.f };
    SColliderBodyAABB2D aabb3Body = { { 50.f, 50.f } };
    ECollisionPolicyFlags aabb3Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D aabb4 = colored_polygon_templates::coloredPolygonSquare( 25.f );
    vec2f aabb4Pos { 700.f, 300.f };
    vec2f aabb4Scale { 4.f, 4.f };
    SColliderBodyAABB2D aabb4Body = { { 25.f, 25.f } };
    ECollisionPolicyFlags aabb4Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D point = colored_polygon_templates::coloredPolygonSquare( 4.f );
    point.color = { 0.f, 0.f, 1.f, 1.f };
    vec2f pointPos { 0.f, 0.f };
    ECollisionPolicyFlags pointPolicy = ECollisionPolicyFlags::AFFECTED;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        pointPos = vecCastType<float>( mousePos );


        if( resolvePoint2DVsAABB2D( pointPos, pointPolicy, aabb1Pos, vec2f(1.f), aabb1Body, aabb1Policy ) )
        {
            aabb1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsAABB2D( pointPos, pointPolicy, aabb2Pos, vec2f(1.f), aabb2Body, aabb2Policy ) )
        {
            aabb2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsAABB2D( pointPos, pointPolicy, aabb3Pos, vec2f(1.f), aabb3Body, aabb3Policy ) )
        {
            aabb3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsAABB2D( pointPos, pointPolicy, aabb4Pos, aabb4Scale, aabb4Body, aabb4Policy ) )
        {
            aabb4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( aabb1, aabb1Pos );
            renderer.submitPolygon( aabb2, aabb2Pos );
            renderer.submitPolygon( aabb3, aabb3Pos );
            renderer.submitPolygon( aabb4, aabb4Pos, aabb4Scale );
            renderer.submitPolygon( point, pointPos );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}


TEST_CASE( "Physics - point vs circle collision", "[interactive][demo]" )
{
    chestnutInit();

    auto window = createWindow( "Point vs circle collision" );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 36 );
    vec2f circle1Pos { 200.f, 200.f };
    SColliderBodyCircle2D circle1Body = { 150.f };
    ECollisionPolicyFlags circle1Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    vec2f circle2Pos { 500.f, 200.f };
    SColliderBodyCircle2D circle2Body = { 50.f };
    ECollisionPolicyFlags circle2Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D circle3 = colored_polygon_templates::coloredPolygonCircle( 200.f, 36 );
    vec2f circle3Pos { 500.f, 400.f };
    float circle3Scale = 0.5f;
    SColliderBodyCircle2D circle3Body = { 200.f };
    ECollisionPolicyFlags circle3Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D point = colored_polygon_templates::coloredPolygonSquare( 4.f );
    point.color = { 0.f, 0.f, 1.f, 1.f };
    vec2f pointPos { 0.f, 0.f };
    ECollisionPolicyFlags pointPolicy = ECollisionPolicyFlags::AFFECTED;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        pointPos = vecCastType<float>( mousePos );


        if( resolvePoint2DVsCircle2D( pointPos, pointPolicy, circle1Pos, 1.f, circle1Body, circle1Policy ) )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsCircle2D( pointPos, pointPolicy, circle2Pos, 1.f, circle2Body, circle2Policy ) )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolvePoint2DVsCircle2D( pointPos, pointPolicy, circle3Pos, circle3Scale, circle3Body, circle3Policy ) )
        {
            circle3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Pos );
            renderer.submitPolygon( circle2, circle2Pos );
            renderer.submitPolygon( circle3, circle3Pos, vec2f( circle3Scale ) );
            renderer.submitPolygon( point, pointPos );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}


TEST_CASE( "Physics - circle vs circle collision", "[interactive][demo]" )
{
    chestnutInit();

    auto window = createWindow( "Circle vs circle collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 36 );
    vec2f circle1Pos { 300.f, 300.f };
    SColliderBodyCircle2D circle1Body = { 150.f };
    ECollisionPolicyFlags circle1Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    vec2f circle2Pos { 800.f, 300.f };
    SColliderBodyCircle2D circle2Body = { 50.f };
    ECollisionPolicyFlags circle2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D circle3 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    vec2f circle3Pos { 500.f, 600.f };
    float circle3Scale = 2.f;
    SColliderBodyCircle2D circle3Body = { 50.f };
    ECollisionPolicyFlags circle3Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 200.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    vec2f circleUserPos;
    float circleUserScale = 0.5f;
    SColliderBodyCircle2D circleUserBody = { 200.f };
    ECollisionPolicyFlags circleUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserPos = vecCastType<float>( mousePos );


        if( resolveCircle2DVsCircle2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, circle1Pos, 1.f, circle1Body, circle1Policy ) )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsCircle2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, circle2Pos, 1.f, circle2Body, circle2Policy ) )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsCircle2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, circle3Pos, circle3Scale, circle3Body, circle3Policy ) )
        {
            circle3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Pos );
            renderer.submitPolygon( circle2, circle2Pos );
            renderer.submitPolygon( circle3, circle3Pos, vec2f( circle3Scale ) );
            renderer.submitPolygon( circleUser, circleUserPos, vec2f( circleUserScale ) );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();   
}


TEST_CASE( "Physics - AABB vs AABB collision", "[interactive][demo]" )
{
    chestnutInit();

    auto window = createWindow( "AABB vs AABB collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );



    SColoredPolygon2D aabb1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    vec2f aabb1Pos { 200.f, 250.f };
    SColliderBodyAABB2D aabb1Body = { { 100.f, 200.f } };
    ECollisionPolicyFlags aabb1Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D aabb2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    vec2f aabb2Pos { 600.f, 250.f };
    SColliderBodyAABB2D aabb2Body = { { 100.f, 50.f } };
    ECollisionPolicyFlags aabb2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D aabb3 = colored_polygon_templates::coloredPolygonRectangle( 150.f, 150.f );
    vec2f aabb3Pos { 1000.f, 250.f };
    SColliderBodyAABB2D aabb3Body = { { 150.f, 150.f } };
    ECollisionPolicyFlags aabb3Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabb4 = colored_polygon_templates::coloredPolygonRectangle( 400.f, 50.f );
    vec2f aabb4Pos { 600.f, 500.f };
    vec2f aabb4Scale { 0.75f, 2.f };
    SColliderBodyAABB2D aabb4Body = { { 400.f, 50.f } };
    ECollisionPolicyFlags aabb4Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabbUser = colored_polygon_templates::coloredPolygonRectangle( 80.f, 120.f );
    aabbUser.color = { 0.f, 0.f, 1.f, 1.f };
    vec2f aabbUserPos;
    SColliderBodyAABB2D aabbUserBody = { { 80.f, 120.f } };
    ECollisionPolicyFlags aabbUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;



    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        aabbUserPos = vecCastType<float>( mousePos );


        if( resolveAABB2DVsAABB2D( aabbUserPos, vec2f(1.f), aabbUserBody, aabbUserPolicy, aabb1Pos, vec2f(1.f), aabb1Body, aabb1Policy ) )
        {
            aabb1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserPos, vec2f(1.f), aabbUserBody, aabbUserPolicy, aabb2Pos, vec2f(1.f), aabb2Body, aabb2Policy ) )
        {
            aabb2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserPos, vec2f(1.f), aabbUserBody, aabbUserPolicy, aabb3Pos, vec2f(1.f), aabb3Body, aabb3Policy ) )
        {
            aabb3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveAABB2DVsAABB2D( aabbUserPos, vec2f(1.f), aabbUserBody, aabbUserPolicy, aabb4Pos, aabb4Scale, aabb4Body, aabb4Policy ) )
        {
            aabb4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( aabb1, aabb1Pos );
            renderer.submitPolygon( aabb2, aabb2Pos );
            renderer.submitPolygon( aabb3, aabb3Pos );
            renderer.submitPolygon( aabb4, aabb4Pos, aabb4Scale );
            renderer.submitPolygon( aabbUser, aabbUserPos );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();   
}


TEST_CASE( "Physics - circle vs AABB collision", "[interactive][demo]" )
{
    chestnutInit();

    auto window = createWindow( "Circle vs AABB collision", 1280, 720 );

    CShaderProgram shader;
    REQUIRE_NOTHROW( shader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );
    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );


    SColoredPolygon2D aabb1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    vec2f aabb1Pos { 100.f, 150.f };
    SColliderBodyAABB2D aabb1Body = { { 100.f, 200.f } };
    ECollisionPolicyFlags aabb1Policy = ECollisionPolicyFlags::NONE;

    SColoredPolygon2D aabb2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    vec2f aabb2Pos { 500.f, 150.f };
    SColliderBodyAABB2D aabb2Body = { { 100.f, 50.f } };
    ECollisionPolicyFlags aabb2Policy = ECollisionPolicyFlags::AFFECTED;

    SColoredPolygon2D aabb3 = colored_polygon_templates::coloredPolygonSquare( 200.f );
    vec2f aabb3Pos { 900.f, 150.f };
    vec2f aabb3Scale { 0.75f, 0.75f };
    SColliderBodyAABB2D aabb3Body = { { 200.f, 200.f } };
    ECollisionPolicyFlags aabb3Policy = ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D aabb4 = colored_polygon_templates::coloredPolygonRectangle( 300.f, 100.f );
    vec2f aabb4Pos { 400.f, 500.f };
    SColliderBodyAABB2D aabb4Body = { { 300.f, 100.f } };
    ECollisionPolicyFlags aabb4Policy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;

    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 25.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    vec2f circleUserPos;
    float circleUserScale = 2.f;
    SColliderBodyCircle2D circleUserBody = { 25.f };
    ECollisionPolicyFlags circleUserPolicy = ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING;


    SDL_Event e;
    
    do 
    {
        SDL_PollEvent(&e);


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserPos = vecCastType<float>( mousePos );


        if( resolveCircle2DVsAABB2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, aabb1Pos, vec2f(1.f), aabb1Body, aabb1Policy ) )
        {
            aabb1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, aabb2Pos, vec2f(1.f), aabb2Body, aabb2Policy ) )
        {
            aabb2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, aabb3Pos, aabb3Scale, aabb3Body, aabb3Policy ) )
        {
            aabb3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( resolveCircle2DVsAABB2D( circleUserPos, circleUserScale, circleUserBody, circleUserPolicy, aabb4Pos, vec2f(1.f), aabb4Body, aabb4Policy ) )
        {
            aabb4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            aabb4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window->clear();
            renderer.clear();
            renderer.submitPolygon( aabb1, aabb1Pos );
            renderer.submitPolygon( aabb2, aabb2Pos );
            renderer.submitPolygon( aabb3, aabb3Pos, aabb3Scale );
            renderer.submitPolygon( aabb4, aabb4Pos );
            renderer.submitPolygon( circleUser, circleUserPos, vec2f( circleUserScale ) );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

    } while( e.type != SDL_QUIT );

    chestnutQuit();
}