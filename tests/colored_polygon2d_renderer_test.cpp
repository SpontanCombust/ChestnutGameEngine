#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/colored_polygon2d_renderer.hpp"
#include "../src/chestnut/engine/maths/vector2.hpp"
#include "../src/chestnut/engine/maths/vector_transform.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Colored polygon renderer test - general presentation", "[manual]" )
{
    const char *testName = "Colored polygon renderer test";

    REQUIRE( chestnutInit( ) );

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( CShaderProgramResource::loadFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

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

    
    showInfoMessageBox( testName, "Click to draw red square, rainbow hexagon and green triangle outline" );
    
    window.clear();
        renderer.clear();
        renderer.submitPolygon( square, {50.f, 50.f} );
        renderer.submitPolygon( hexagon, {400.f, 200.f } );
        renderer.submitPolygon( triangle, { 200.f, 300.f } );
        renderer.render( window.getFramebuffer() );
    window.flipBuffer();

    REQUIRE( showConfirmMessageBox( testName ) );
}   


using namespace chestnut::engine::colored_polygon_templates;

TEST_CASE( "Renderers - Colored polygon renderer test - template polygons", "[manual]" )
{
    const char *testName = "Colored polygon renderer test - template polygons";

    REQUIRE( chestnutInit() );

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CColoredPolygon2DRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( CShaderProgramResource::loadFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) ) );

    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    SColoredPolygon2D triangle1 = coloredPolygonTriangle( 100.f );          triangle1.color = { 1.f, 0.f, 0.f, 1.f };
    SColoredPolygon2D triangle2 = coloredPolygonTriangle( 150.f, 50.f );    triangle2.color = { 1.f, 1.f, 0.f, 1.f };
    SColoredPolygon2D square    = coloredPolygonSquare( 60.f );             square.color    = { 0.f, 1.f, 0.f, 1.f };
    SColoredPolygon2D rectangle = coloredPolygonRectangle( 40.f, 100.f );   rectangle.color = { 0.f, 1.f, 1.f, 1.f };
    SColoredPolygon2D circle    = coloredPolygonCircle( 30.f, 36 );         circle.color    = { 0.f, 0.f, 1.f, 1.f };


    showInfoMessageBox( testName, "Click to render:\n"
                                     "-red equal side triangle\n"
                                     "-yellow wide triangle\n"
                                     "-green square\n"
                                     "-cyan rectangle\n"
                                     "-blue circle");

    window.clear();
        renderer.clear();
        renderer.submitPolygon( triangle1, { 100.f, 100.f } );
        renderer.submitPolygon( triangle2, { 250.f, 100.f } );
        renderer.submitPolygon( square, { 400.f, 100.f } );
        renderer.submitPolygon( rectangle, { 100.f, 300.f } );
        renderer.submitPolygon( circle, { 200.f, 300.f } );
        renderer.render( window.getFramebuffer() );
    window.flipBuffer();


    REQUIRE( showConfirmMessageBox( testName ) );
}