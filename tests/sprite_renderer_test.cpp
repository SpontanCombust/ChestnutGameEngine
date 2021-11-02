#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/sprite_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Sprite renderer test", "[manual]" )
{
    const char *testName = "Sprite renderer test";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );

    CSpriteRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.frag" ) ) );

    CTexture2D tex;
    REQUIRE_NOTHROW( tex = CTexture2D( loadTexture2DResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/awesomeface.png" ) ) );


    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    
    SECTION( "Render missing texture" )
    {
        CTexture2D missing;

        showInfoMessageBox( testName, "Click to render an image with missing texture" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( missing, {0,0}, {0,0}, {64.f, 64.f} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    window.clear();
        renderer.clear();
        renderer.submitSprite( tex, {0,0} );
        renderer.render( window.getFramebuffer() );
    window.flipBuffer();

    SECTION( "Default values" )
    {
        showInfoMessageBox( testName, "Click to render an image with default values" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( tex, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Scaled up" )
    {
        SECTION( "With default linear filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled up image around its center with linear filtering" );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled up image around its center with nearest filtering" );

            tex.setFiltering( GL_NEAREST, GL_NEAREST );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Scaled down" )
    {
        SECTION( "With default linear filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled down image around its center with linear filtering" );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled down image around its center with nearest filtering" );

            tex.setFiltering( GL_NEAREST, GL_NEAREST );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Rotated" )
    {
        showInfoMessageBox( testName, "Click to render a texture rotated around its center" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {1,1}, CHESTNUT_PI / 2.f );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Clipping rectangle" )
    {
        SECTION( "Smaller than texture size" )
        {
            showInfoMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to center" );

            tex.setClippingRect( SRectangle{ 0.f, 0.f, tex.getWidth() / 2.f, tex.getHeight() / 2.f } );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, {0,0} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "Bigger than texture size" )
        {
            showInfoMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to 1.5 times past lower right corner" );

            tex.setClippingRect( SRectangle{ 0.f, 0.f, tex.getWidth() * 1.5f, tex.getHeight() * 1.5f } );

            window.clear();
                renderer.clear();
                renderer.submitSprite( tex, {0,0} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Tint" )
    {
        showInfoMessageBox( testName, "Click to render a texture with 50% red tint" );

        tex.setTint( vec3f{ 1.f, 0.f, 0.f } );
        tex.setTintFactor( 0.5f );

        window.clear();
            renderer.clear();
            renderer.submitSprite( tex, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    chestnutQuit();
    sleepFor(1000);
}