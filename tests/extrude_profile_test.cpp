#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/plain_mesh_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/maths/angles.hpp"
#include "../src/chestnut/engine/graphics/algorithms/extrude_profile.hpp"


using namespace chestnut::engine;

TEST_CASE( "Extrude profile", "[manual]" )
{
    const char *testName = "Extrude profile";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CPlainMeshRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );


    std::vector<vec2f> profile {
        vec2f(0.f, 0.4f),
        vec2f(0.2f, 0.f),
        vec2f(0.f, -0.4f),
        vec2f(-0.2f, 0.f),
    };

    std::vector<SBezierCurvePoint> curvePoints {
        {{-5.f, 0.f, 0.f}, 0.3f},
        {{-2.f, 7.f, -1.f}, 1.f},
        {{5.f, 0.f, -2.f}, 1.f},
        {{2.f, 7.f, -3.f}, 0.1f},
    };
    
    CMesh mesh;
    REQUIRE_NOTHROW(mesh = CMesh(*extrudeProfileWithCurve(profile, curvePoints, 100)));

    CTexture2D textureDiffuse;
    REQUIRE_NOTHROW( textureDiffuse = CTexture2D( *CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/marble.png" ) ) );
    mesh.getResource()->m_material.diffuse = textureDiffuse;


    showInfoMessageBox( testName, "Click to render a N-shaped curve extruded along a profile." );

    renderer.setProjectionMatrix(matMakePerspective( degreesToRadians(60.f), (float)window.getSizeWidth() / (float)window.getSizeHeight(), 0.1f, 100.f));
    renderer.setViewMatrix(matMakeLookAt(vec3f(0.f, 3.5f, 8.f), vec3f(0.f, 3.5f, 0.f), vec3f(0.f, 1.f, 0.f)));

    window.clear();
        renderer.clear();
        renderer.submitMesh(mesh, {0.f, 0.f, 0.f});
        renderer.render( window.getFramebuffer() );
    window.flipBuffer();

    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
}