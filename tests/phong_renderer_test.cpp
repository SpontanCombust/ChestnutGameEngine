#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/phong_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Phong renderer test", "[manual]" )
{
    const char *testName = "Phong renderer test";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    REQUIRE(GLEW_VERSION_3_3);

    CPhongRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );

    CMesh mesh;
    REQUIRE_NOTHROW( mesh = CMesh( *CMeshResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/models/suzanne.obj" ) ) );

    std::shared_ptr<CTexture2DResource> textureDiffuse;
    REQUIRE_NOTHROW( textureDiffuse = *CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/marble.png" ) );
    mesh.getResource()->m_material.diffuse = textureDiffuse;




    SECTION("Basic example")
    {
        showInfoMessageBox( testName, "Click to render a mesh with default values" );

        renderer.setProjectionMatrix(matMakePerspective(80.f, (float)window.getSizeWidth() / (float)window.getSizeHeight(), 0.1f, 100.f));
        renderer.setViewMatrix(matMakeLookAt(vec3f(0.f, 0.f, 2.f), vec3f(0.f, 0.f, 0.f)));

        window.clear();
            renderer.clear();
            renderer.submitMesh(mesh, {0.f, 0.f, 0.f});
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }


    chestnutQuit();
}