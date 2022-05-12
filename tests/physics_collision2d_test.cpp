#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/physics/collider2d.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d.hpp"
#include "../src/chestnut/engine/graphics/renderers/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector_cast.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include <SDL_events.h>


using namespace chestnut::engine;

TEST_CASE( "Physics - point vs AABB collision", "[manual][demo]" )
{
    chestnutInit();

    CWindow window( "Point vs AABB collision" );
    REQUIRE( window.isValid() );
    window.toggleVsync( true );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D box1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 300.f );
    CBoxCollider2D box1Collider;
    box1Collider.setPosition(vec2f( 100.f, 250.f ));
    box1Collider.setSize(vec2f(100.f, 300.f));
    box1Collider.setPolicyFlags(ECollisionPolicyFlags::NONE);

    SColoredPolygon2D box2 = colored_polygon_templates::coloredPolygonRectangle( 200.f, 100.f );
    CBoxCollider2D box2Collider;
    box2Collider.setPosition(vec2f( 400.f, 250.f ));
    box2Collider.setSize(vec2f(200.f, 100.f));
    box2Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D box3 = colored_polygon_templates::coloredPolygonSquare( 50.f );
    CBoxCollider2D box3Collider;
    box3Collider.setPosition(vec2f( 400.f, 500.f ));
    box3Collider.setSize(vec2f(50.f, 50.f));
    box3Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED);

    SColoredPolygon2D box4 = colored_polygon_templates::coloredPolygonSquare( 25.f );
    CBoxCollider2D box4Collider;
    box4Collider.setPosition(vec2f( 700.f, 300.f ));
    box4Collider.setScale(vec2f(4.f, 4.f));
    box4Collider.setSize(vec2f(25.f, 25.f));
    box4Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTING);
    
    SColoredPolygon2D point = colored_polygon_templates::coloredPolygonSquare( 4.f );
    point.color = { 0.f, 0.f, 1.f, 1.f };
    CPointCollider2D pointCollider;
    pointCollider.setPosition(vec2f(0.f, 0.f));
    pointCollider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);


    SDL_Event e;
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT || (e.type ==  SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) )
            {
                quit = true;
            }
        }


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        pointCollider.setPosition(vecCastType<float>( mousePos ));


        if( pointCollider.resolveCollision(box1Collider).isCollision )
        {
            box1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( pointCollider.resolveCollision(box2Collider).isCollision )
        {
            box2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( pointCollider.resolveCollision(box3Collider).isCollision )
        {
            box3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( pointCollider.resolveCollision(box4Collider).isCollision )
        {
            box4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window.clear();
            renderer.clear();
            renderer.submitPolygon( box1, box1Collider.getPosition() );
            renderer.submitPolygon( box2, box2Collider.getPosition() );
            renderer.submitPolygon( box3, box3Collider.getPosition() );
            renderer.submitPolygon( box4, box4Collider.getPosition(), box4Collider.getScale() );
            renderer.submitPolygon( point, pointCollider.getPosition() );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

    }

    chestnutQuit();
}


TEST_CASE( "Physics - point vs circle collision", "[manual][demo]" )
{
    chestnutInit();

    CWindow window( "Point vs circle collision" );
    REQUIRE( window.isValid() );
    window.toggleVsync( true );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 36 );
    CCircleCollider2D circle1Collider;
    circle1Collider.setPosition(vec2f(200.f, 200.f));
    circle1Collider.setRadius(150.f);
    circle1Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    CCircleCollider2D circle2Collider;
    circle2Collider.setPosition(vec2f(500.f, 200.f));
    circle2Collider.setRadius(50.f);
    circle2Collider.setPolicyFlags(ECollisionPolicyFlags::NONE);

    SColoredPolygon2D circle3 = colored_polygon_templates::coloredPolygonCircle( 200.f, 36 );
    CCircleCollider2D circle3Collider;
    circle3Collider.setPosition(vec2f(500.f, 400.f));
    circle3Collider.setRadius(200.f);
    circle3Collider.setScale(vec2f(0.5f));
    circle3Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D point = colored_polygon_templates::coloredPolygonSquare( 4.f );
    point.color = { 0.f, 0.f, 1.f, 1.f };
    CPointCollider2D pointCollider;
    pointCollider.setPosition(vec2f(0.f, 0.f));
    pointCollider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED);


    SDL_Event e;
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT || (e.type ==  SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) )
            {
                quit = true;
            }
        }


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        pointCollider.setPosition(vecCastType<float>( mousePos ));


        if( pointCollider.resolveCollision(circle1Collider).isCollision )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( pointCollider.resolveCollision(circle2Collider).isCollision )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( pointCollider.resolveCollision(circle3Collider).isCollision )
        {
            circle3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window.clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Collider.getPosition() );
            renderer.submitPolygon( circle2, circle2Collider.getPosition() );
            renderer.submitPolygon( circle3, circle3Collider.getPosition(), circle3Collider.getScale() );
            renderer.submitPolygon( point, pointCollider.getPosition() );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

    }

    chestnutQuit();
}


TEST_CASE( "Physics - circle vs circle collision", "[manual][demo]" )
{
    chestnutInit();

    CWindow window( "Circle vs circle collision", 1280, 720 );
    REQUIRE( window.isValid() );
    window.toggleVsync( true );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );

    SColoredPolygon2D circle1 = colored_polygon_templates::coloredPolygonCircle( 150.f, 36 );
    CCircleCollider2D circle1Collider;
    circle1Collider.setPosition(vec2f(300.f, 300.f));
    circle1Collider.setRadius(150.f);
    circle1Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D circle2 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    CCircleCollider2D circle2Collider;
    circle2Collider.setPosition(vec2f(800.f, 300.f));
    circle2Collider.setRadius(50.f);
    circle2Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED);
    
    SColoredPolygon2D circle3 = colored_polygon_templates::coloredPolygonCircle( 50.f, 36 );
    CCircleCollider2D circle3Collider;
    circle3Collider.setPosition(vec2f(500.f, 600.f));
    circle3Collider.setRadius(50.f);
    circle3Collider.setScale(vec2f(2.f));
    circle3Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);
    
    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 200.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    CCircleCollider2D circleUserCollider;
    circleUserCollider.setScale(vec2f(0.5f));
    circleUserCollider.setRadius(200.f);
    circleUserCollider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SDL_Event e;
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT || (e.type ==  SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) )
            {
                quit = true;
            }
        }


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserCollider.setPosition(vecCastType<float>( mousePos ));


        if( circleUserCollider.resolveCollision(circle1Collider).isCollision )
        {
            circle1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( circleUserCollider.resolveCollision(circle2Collider).isCollision )
        {
            circle2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( circleUserCollider.resolveCollision(circle3Collider).isCollision )
        {
            circle3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            circle3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window.clear();
            renderer.clear();
            renderer.submitPolygon( circle1, circle1Collider.getPosition() );
            renderer.submitPolygon( circle2, circle2Collider.getPosition() );
            renderer.submitPolygon( circle3, circle3Collider.getPosition(), circle3Collider.getScale() );
            renderer.submitPolygon( circleUser, circleUserCollider.getPosition(), circleUserCollider.getScale() );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

    }

    chestnutQuit();   
}


TEST_CASE( "Physics - AABB vs AABB collision", "[manual][demo]" )
{
    chestnutInit();

    CWindow window( "AABB vs AABB collision", 1280, 720 );
    REQUIRE( window.isValid() );
    window.toggleVsync( true );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );



    SColoredPolygon2D box1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    CBoxCollider2D box1Collider;
    box1Collider.setPosition(vec2f(200.f, 250.f));
    box1Collider.setSize(vec2f(100.f, 200.f));
    box1Collider.setPolicyFlags(ECollisionPolicyFlags::NONE);

    SColoredPolygon2D box2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    CBoxCollider2D box2Collider;
    box2Collider.setPosition(vec2f(600.f, 250.f));
    box2Collider.setSize(vec2f(100.f, 50.f));
    box2Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED);

    SColoredPolygon2D box3 = colored_polygon_templates::coloredPolygonRectangle( 150.f, 150.f );
    CBoxCollider2D box3Collider;
    box3Collider.setPosition(vec2f(1000.f, 250.f));
    box3Collider.setSize(vec2f(150.f, 150.f));
    box3Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTING);
    
    SColoredPolygon2D box4 = colored_polygon_templates::coloredPolygonRectangle( 400.f, 50.f );
    CBoxCollider2D box4Collider;
    box4Collider.setPosition(vec2f(600.f, 500.f));
    box4Collider.setSize(vec2f(400.f, 50.f));
    box4Collider.setScale(vec2f(0.75f, 2.f));
    box4Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D boxUser = colored_polygon_templates::coloredPolygonRectangle( 80.f, 120.f );
    boxUser.color = { 0.f, 0.f, 1.f, 1.f };
    CBoxCollider2D boxUserCollider;
    boxUserCollider.setSize(vec2f(80.f, 120.f));
    boxUserCollider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SDL_Event e;
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT || (e.type ==  SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) )
            {
                quit = true;
            }
        }


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        boxUserCollider.setPosition(vecCastType<float>( mousePos ));


        if( boxUserCollider.resolveCollision(box1Collider).isCollision )
        {
            box1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( boxUserCollider.resolveCollision(box2Collider).isCollision )
        {
            box2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( boxUserCollider.resolveCollision(box3Collider).isCollision )
        {
            box3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( boxUserCollider.resolveCollision(box4Collider).isCollision )
        {
            box4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window.clear();
            renderer.clear();
            renderer.submitPolygon( box1, box1Collider.getPosition() );
            renderer.submitPolygon( box2, box2Collider.getPosition() );
            renderer.submitPolygon( box3, box3Collider.getPosition() );
            renderer.submitPolygon( box4, box4Collider.getPosition(), box4Collider.getScale() );
            renderer.submitPolygon( boxUser, boxUserCollider.getPosition(), boxUserCollider.getScale() );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

    }

    chestnutQuit();   
}


TEST_CASE( "Physics - circle vs AABB collision", "[manual][demo]" )
{
    chestnutInit();

    CWindow window( "Circle vs AABB collision", 1280, 720 );
    REQUIRE( window.isValid() );
    window.toggleVsync( true );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 1280, 720, 0, -1, 1 ) );


    SColoredPolygon2D box1 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 200.f );
    CBoxCollider2D box1Collider;
    box1Collider.setPosition(vec2f(100.f, 150.f));
    box1Collider.setSize(vec2f(100.f, 200.f));
    box1Collider.setPolicyFlags(ECollisionPolicyFlags::NONE);
    
    SColoredPolygon2D box2 = colored_polygon_templates::coloredPolygonRectangle( 100.f, 50.f );
    CBoxCollider2D box2Collider;
    box2Collider.setPosition(vec2f(500.f, 150.f));
    box2Collider.setSize(vec2f(100.f, 50.f));
    box2Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED);
    
    SColoredPolygon2D box3 = colored_polygon_templates::coloredPolygonSquare( 200.f );
    CBoxCollider2D box3Collider;
    box3Collider.setPosition(vec2f(900.f, 150.f));
    box3Collider.setSize(vec2f(200.f, 200.f));
    box3Collider.setScale(vec2f(0.75f, 0.75f));
    box3Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D box4 = colored_polygon_templates::coloredPolygonRectangle( 300.f, 100.f );
    CBoxCollider2D box4Collider;
    box4Collider.setPosition(vec2f(400.f, 500.f));
    box4Collider.setSize(vec2f(300.f, 100.f));
    box4Collider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);

    SColoredPolygon2D circleUser = colored_polygon_templates::coloredPolygonCircle( 25.f, 36 );
    circleUser.color = { 0.f, 0.f, 1.f, 1.f };
    CCircleCollider2D circleUserCollider;
    circleUserCollider.setScale(vec2f(2.f));
    circleUserCollider.setRadius(25.f);
    circleUserCollider.setPolicyFlags(ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING);
    

    SDL_Event e;
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT || (e.type ==  SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) )
            {
                quit = true;
            }
        }


        vec2i mousePos;
        SDL_GetMouseState( &mousePos.x, &mousePos.y );
        circleUserCollider.setPosition(vecCastType<float>( mousePos ));


        if( circleUserCollider.resolveCollision(box1Collider).isCollision )
        {
            box1.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box1.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( circleUserCollider.resolveCollision(box2Collider).isCollision )
        {
            box2.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box2.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( circleUserCollider.resolveCollision(box3Collider).isCollision )
        {
            box3.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box3.color = { 1.f, 1.f, 1.f, 1.f };
        }
        if( circleUserCollider.resolveCollision(box4Collider).isCollision )
        {
            box4.color = { 1.f, 0.f, 0.f, 1.f };
        }
        else
        {
            box4.color = { 1.f, 1.f, 1.f, 1.f };
        }
        
        
        window.clear();
            renderer.clear();
            renderer.submitPolygon( box1, box1Collider.getPosition() );
            renderer.submitPolygon( box2, box2Collider.getPosition() );
            renderer.submitPolygon( box3, box3Collider.getPosition(), box3Collider.getScale() );
            renderer.submitPolygon( box4, box4Collider.getPosition() );
            renderer.submitPolygon( circleUser, circleUserCollider.getPosition(),circleUserCollider.getScale() );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

    }

    chestnutQuit();
}

// TODO automatic unit tests 
// TODO collision system test