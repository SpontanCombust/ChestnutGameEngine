#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/phong_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/maths/angles.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Phong renderer test", "[manual]" )
{
    const char *testName = "Phong renderer test";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CPhongRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );

    CMesh mesh;
    REQUIRE_NOTHROW( mesh = CMesh( CMeshResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/models/suzanne.obj" ).value() ) );

    CTexture2D textureDiffuse;
    REQUIRE_NOTHROW( textureDiffuse = CTexture2D( CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/marble.png" ).value() ) );
    mesh.getResource()->m_material.diffuse = textureDiffuse;




    SECTION("Default texture maps")
    {
        showInfoMessageBox( testName, "Click to render a mesh with default values" );

        renderer.setProjectionMatrix(matMakePerspective(degreesToRadians(60.f), (float)window.getSizeWidth() / (float)window.getSizeHeight(), 0.1f, 100.f));
        renderer.setViewMatrix(matMakeLookAt(vec3f(0.f, 0.f, 3.f), vec3f(0.f, 0.f, 0.f)));

        CDirectionalLight light;
        light.m_direction = {1.f, -1.f, 0.f};
        light.m_ambient = {0.1f, 0.1f, 0.1f};
        light.m_diffuse = {0.8f, 0.8f, 0.8f};
        light.m_specular = {0.5f, 0.5f, 0.5f};

        window.clear();
            renderer.clear();
            renderer.submitMesh(mesh, {0.f, 0.f, 0.f});
            renderer.submitLight(light);
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }



    chestnutQuit();
    sleepFor(1000);
}