#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/sprite_renderer.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Sprite renderer test", "[manual]" )
{
    const char *testName = "Sprite renderer test";

    chestnutInit();

    CWindow window( testName );

    CSpriteRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );

    CSprite sprite;
    REQUIRE_NOTHROW( sprite = CSprite( CTexture2DResource::loadFromImageFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/images/awesomeface.png" ).value() ) );


    renderer.setViewMatrix( mat4f() );
    renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    
    SECTION( "Render missing texture" )
    {
        CSprite missing;

        showInfoMessageBox( testName, "Click to render an image with missing texture" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( missing, {0,0}, {0,0}, {64.f, 64.f} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Default values" )
    {
        showInfoMessageBox( testName, "Click to render an image with default values" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Scaled up" )
    {
        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        SECTION( "With default linear filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled up image around its center with linear filtering" );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, { sprite.getWidth() / 2.f, sprite.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled up image around its center with nearest filtering" );

            sprite.setFiltering( GL_NEAREST, GL_NEAREST );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, { sprite.getWidth() / 2.f, sprite.getHeight() / 2.f}, {0.5,0.5}, {2.f,1.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Scaled down" )
    {
        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();
        
        SECTION( "With default linear filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled down image around its center with linear filtering" );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, { sprite.getWidth() / 2.f, sprite.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "With nearest filtering" )
        {
            showInfoMessageBox( testName, "Click to render a scaled down image around its center with nearest filtering" );

            sprite.setFiltering( GL_NEAREST, GL_NEAREST );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, { sprite.getWidth() / 2.f, sprite.getHeight() / 2.f}, {0.5,0.5}, {0.25f,0.5f} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Rotated" )
    {
        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showInfoMessageBox( testName, "Click to render a texture rotated around its center" );

        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, { sprite.getWidth() / 2.f, sprite.getHeight() / 2.f}, {0.5,0.5}, {1,1}, CHESTNUT_PI / 2.f );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Clipping rectangle" )
    {
        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        SECTION( "Smaller than texture size" )
        {
            showInfoMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to center" );

            sprite.setClippingRect( SRectangle{ 0.f, 0.f, sprite.getWidth() / 2.f, sprite.getHeight() / 2.f } );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, {0,0} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }

        SECTION( "Bigger than texture size" )
        {
            showInfoMessageBox( testName, "Click to render a texture with clipping rectangle going from upper left corner to 1.5 times past lower right corner" );

            sprite.setClippingRect( SRectangle{ 0.f, 0.f, sprite.getWidth() * 1.5f, sprite.getHeight() * 1.5f } );

            window.clear();
                renderer.clear();
                renderer.submitSprite( sprite, {0,0} );
                renderer.render( window.getFramebuffer() );
            window.flipBuffer();

            REQUIRE( showConfirmMessageBox( testName ) );
        }
    }

    SECTION( "Tint" )
    {
        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showInfoMessageBox( testName, "Click to render a texture with 50% red tint" );

        sprite.setTint( vec3f{ 1.f, 0.f, 0.f } );
        sprite.setTintFactor( 0.5f );

        window.clear();
            renderer.clear();
            renderer.submitSprite( sprite, {0,0} );
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    chestnutQuit();
    sleepFor(1000);
}