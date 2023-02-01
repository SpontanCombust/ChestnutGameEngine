#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/renderers/text_renderer.hpp"
#include "../src/chestnut/engine/graphics/renderers/sprite_renderer.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include "test_utils.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Framebuffer test", "[manual]" )
{
    const char *testName = "Renderers - Framebuffer test";

    chestnutInit();

    CWindow window( testName );

    CTextRenderer textRenderer;
    REQUIRE_NOTHROW( textRenderer.init() );
    textRenderer.setViewMatrix( mat4f() );
    textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, (float)window.getWidth(), (float)window.getHeight(), 0, -1, 1 ) ); 

    CSpriteRenderer spriteRenderer;
    REQUIRE_NOTHROW( spriteRenderer.init() );
    spriteRenderer.setViewMatrix( mat4f() );
    spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, (float)window.getWidth(), (float)window.getHeight(), 0, -1, 1 ) ); 

    CText text;
    REQUIRE_NOTHROW( text = CText( CFontResource::load( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/fonts/arial.ttf" ).value(), 32 ) );
    text.append( L"This is an example text.\n" );
    text.append( L"Remember how it looks!", EFontStyle::BOLD, vec3f{ 1.f, 0.f, 0.f } );
    text.generateData();


    showInfoMessageBox( testName, "This test should show the same results received through direct and indirect (through target texture) rendering of text." );


    window.clear();
        textRenderer.clear();
        textRenderer.submitText( text, vec2f{ 50.f, 50.f } );
        textRenderer.render( window.getFramebuffer() );
    window.flipBuffer();

    showInfoMessageBox( testName, "This is a text rendered directly onto screen." );


    CTexture2D blank;
    REQUIRE_NOTHROW( blank = CTexture2D( *CTexture2DResource::loadFromPixels( nullptr, window.getWidth(), window.getHeight(), 4) ) );
    CFramebuffer blankFramebuffer( blank );
    blankFramebuffer.setClearColor( vec4f( 0.f ) ); 
    blankFramebuffer.bind();
    blankFramebuffer.clear();

    window.clear();
        textRenderer.render( blankFramebuffer ); // retains the render data from previous pass

        spriteRenderer.submitTexture( blank, vec2f( 0.f ) );
        spriteRenderer.render( window.getFramebuffer() );
    window.flipBuffer();

    showInfoMessageBox( testName, "This is a text rendered first onto a sprite and then that sprite is rendered onto screen." );


    REQUIRE( showConfirmMessageBox( testName ) );


    chestnutQuit();
}