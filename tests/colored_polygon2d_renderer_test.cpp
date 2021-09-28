#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector2.hpp"
#include "../src/chestnut/engine/maths/vector_transform.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut;

TEST_CASE( "Colored polygon renderer test", "[interactive]" )
{
    const char *testName = "Colored polygon renderer test";

    REQUIRE( chestnutInit( ) );

    auto window = createWindow( testName );

    CShaderProgram shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );

    CColoredPolygon2DRenderer renderer;
    renderer.init( shader );

    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    CColoredPolygon2D square;
    REQUIRE_THROWS( square.addIndices(0,1,2) );
    square.addVertex( {0,0}, 1.f, 0.f, 0.f, 1.f );
    square.addVertex( {200,0}, 0.f, 1.f, 0.f, 1.f );
    square.addVertex( {200,200}, 0.f, 0.f, 1.f, 1.f );
    square.addVertex( {0,200}, 1.f, 1.f, 1.f, 1.f );
    square.addIndices( 0, 1, 2 );
    square.addIndices( 2, 3, 0 );

    CColoredPolygon2D hexagon;
    hexagon.addVertex( { 0.f, 0.f }, {1.f, 1.f, 1.f, 1.f} );
    vec2f vertex;
    vertex = {100.f, 0.f};
    hexagon.addVertex( vertex, {1.f, 0.f, 0.f, 1.f} );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.addVertex( vertex, {0.f, 1.f, 0.f, 1.f} );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.addVertex( vertex, {0.f, 0.f, 1.f, 1.f} );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.addVertex( vertex, {1.f, 0.f, 0.f, 1.f} );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.addVertex( vertex, {0.f, 1.f, 0.f, 1.f} );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.addVertex( vertex, {0.f, 0.f, 1.f, 1.f} );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 1, 2 ) );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 2, 3 ) );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 3, 4 ) );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 4, 5 ) );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 5, 6 ) );
    REQUIRE_NOTHROW( hexagon.addIndices( 0, 6, 1 ) );

    
    showRunTestMessageBox( testName, "Click to draw square and hexagon" );

    window->clear();
        renderer.clear();
        renderer.submitPolygon( square, {50.f, 50.f} );
        renderer.submitPolygon( hexagon, {400.f, 200.f } );
        renderer.render();
    window->flipBuffer();

    showConfirmTestMessageBox( testName );
}   