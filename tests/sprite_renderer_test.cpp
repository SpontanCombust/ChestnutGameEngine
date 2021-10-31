#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/sprite_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Sprite renderer test", "[interactive]" )
{
    const char *testName = "Sprite renderer test";

    chestnutInit();

    auto window = createWindow( testName );
    REQUIRE( window );

    CShaderProgram shader( loadShaderProgramResourceFromFiles( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );

    CSpriteRenderer renderer;
    REQUIRE_NOTHROW( renderer.init( shader ) );

    auto texResource = loadTexture2DResourceFromFile( "../assets/images/awesomeface.png" );
    REQUIRE( texResource->isValid() );

    CTexture2D tex( texResource );


    renderer.bindShader();
    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    
    SECTION( "Render missing texture" )
    {
        CTexture2D missing;

        showRunTestMessageBox( testName, "Click to render an image with missing texture" );

        window->clear();
            renderer.clear();
            renderer.submitSprite( missing, {0,0}, {0,0}, {64.f, 64.f} );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    window->clear();
        renderer.clear();
        renderer.submitSprite( tex, {0,0} );
        renderer.render( window->getFramebuffer() );
    window->flipBuffer();

    SECTION( "Default values" )
    {
        showRunTestMessageBox( testName, "Click to render an image with default values" );

        window->clear();
            renderer.clear();
            renderer.submitSprite( tex, {0,0} );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    SECTION( "Scaled up" )
    {
        SECTION( "With default linear filtering" )
        {
            showRunTestMessageBox( testName, "Click to render a scaled up image around its center with linear filtering" );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showRunTestMessageBox( testName, "Click to render a scaled up image around its center with nearest filtering" );

            tex.setFiltering( GL_NEAREST, GL_NEAREST );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }
    }

    SECTION( "Scaled down" )
    {
        SECTION( "With default linear filtering" )
        {
            showRunTestMessageBox( testName, "Click to render a scaled down image around its center with linear filtering" );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showRunTestMessageBox( testName, "Click to render a scaled down image around its center with nearest filtering" );

            tex.setFiltering( GL_NEAREST, GL_NEAREST );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }
    }

    SECTION( "Rotated" )
    {
        showRunTestMessageBox( testName, "Click to render a texture rotated around its center" );

        window->clear();
            renderer.clear();
            renderer.submitSprite( tex, { tex.getWidth() / 2.f, tex.getHeight() / 2.f}, {0.5,0.5}, {1,1}, CHESTNUT_PI / 2.f );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    SECTION( "Clipping rectangle" )
    {
        SECTION( "Smaller than texture size" )
        {
            showRunTestMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to center" );

            tex.setClippingRect( SRectangle{ 0.f, 0.f, tex.getWidth() / 2.f, tex.getHeight() / 2.f } );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, {0,0} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }

        SECTION( "Bigger than texture size" )
        {
            showRunTestMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to 1.5 times past lower right corner" );

            tex.setClippingRect( SRectangle{ 0.f, 0.f, tex.getWidth() * 1.5f, tex.getHeight() * 1.5f } );

            window->clear();
                renderer.clear();
                renderer.submitSprite( tex, {0,0} );
                renderer.render( window->getFramebuffer() );
            window->flipBuffer();

            REQUIRE( showConfirmTestMessageBox( testName ) );
        }
    }

    SECTION( "Tint" )
    {
        showRunTestMessageBox( testName, "Click to render a texture with 50% red tint" );

        tex.setTint( vec3f{ 1.f, 0.f, 0.f } );
        tex.setTintFactor( 0.5f );

        window->clear();
            renderer.clear();
            renderer.submitSprite( tex, {0,0} );
            renderer.render( window->getFramebuffer() );
        window->flipBuffer();

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    chestnutQuit();
    sleepFor(1000);
}