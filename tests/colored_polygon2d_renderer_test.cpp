#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector2.hpp"
#include "../src/chestnut/engine/maths/vector_transform.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut::engine;

TEST_CASE( "Colored polygon renderer test", "[interactive]" )
{
    const char *testName = "Colored polygon renderer test";

    REQUIRE( chestnutInit( ) );

    auto window = createWindow( testName );

    CShaderProgram shader = CShaderProgram( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );

    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SColoredPolygon2D square;
    square.color = { 1.f, 0.f, 0.f, 1.f };
    square.vecVertices.push_back( vec2f{ 0.f, 0.f } );
    square.vecVertices.push_back( vec2f{ 200.f, 0.f } );
    square.vecVertices.push_back( vec2f{ 200.f, 200.f } );
    square.vecVertices.push_back( vec2f{ 0.f, 200.f } );
    square.vecIndices.insert( square.vecIndices.end(), { 0, 1, 2, 2, 3, 0 } );

    SMulticoloredPolygon2D hexagon;
    hexagon.vecVertices.push_back( SColoredVertex2D( { 0.f, 0.f }, {1.f, 1.f, 1.f, 1.f} ) );
    vec2f vertex;
    vertex = {100.f, 0.f};
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {1.f, 0.f, 0.f, 1.f} ) );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {0.f, 1.f, 0.f, 1.f} ) );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {0.f, 0.f, 1.f, 1.f} ) );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {1.f, 0.f, 0.f, 1.f} ) );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {0.f, 1.f, 0.f, 1.f} ) );
    vecRotate( vertex, CHESTNUT_PI  / 3.f );
    hexagon.vecVertices.push_back( SColoredVertex2D( vertex, {0.f, 0.f, 1.f, 1.f} ) );
    hexagon.vecIndices.insert( hexagon.vecIndices.end(), { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1 } );

    SColoredPolygon2D triangle;
    triangle.color = { 0.f, 1.f, 0.f, 1.f };
    triangle.drawMode = GL_LINES;
    triangle.vecVertices.push_back( vec2f{ 0.f, 0.f } );
    triangle.vecVertices.push_back( vec2f{ -50.f, 100.f } );
    triangle.vecVertices.push_back( vec2f{ 50.f, 100.f } );
    triangle.vecIndices.insert( triangle.vecIndices.end(), { 0, 1, 1, 2, 2, 0 } );

    
    showRunTestMessageBox( testName, "Click to draw red square, rainbow hexagon and green triangle outline" );
    
    window->clear();
        renderer.clear();
        renderer.submitPolygon( square, {50.f, 50.f} );
        renderer.submitPolygon( hexagon, {400.f, 200.f } );
        renderer.submitPolygon( triangle, { 200.f, 300.f } );
        renderer.render();
    window->flipBuffer();

    REQUIRE( showConfirmTestMessageBox( testName ) );
}   