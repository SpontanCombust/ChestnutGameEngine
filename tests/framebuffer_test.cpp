#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/text_renderer.hpp"
#include "../src/chestnut/engine/graphics/sprite_renderer.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include "test_utils.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Framebuffer test", "[interactive]" )
{
    const char *testName = "Renderers - Framebuffer test";

    chestnutInit();

    auto window = createWindow( testName );

    CShaderProgram textShader;
    REQUIRE_NOTHROW( textShader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.frag" ) ) );
    CTextRenderer textRenderer;
    REQUIRE_NOTHROW( textRenderer.init( textShader ) );
    textRenderer.bindShader();
    textRenderer.setViewMatrix( mat4f() );
    textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, window->getSizeWidth(), window->getSizeHeight(), 0, -1, 1 ) ); 

    CShaderProgram spriteShader;
    REQUIRE_NOTHROW( spriteShader = CShaderProgram( loadShaderProgramResourceFromFiles( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.frag" ) ) );
    CSpriteRenderer spriteRenderer;
    REQUIRE_NOTHROW( spriteRenderer.init( spriteShader ) );
    spriteRenderer.bindShader();
    spriteRenderer.setViewMatrix( mat4f() );
    spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, window->getSizeWidth(), window->getSizeHeight(), 0, -1, 1 ) ); 


    showInfoMessageBox( testName, "This test should show the same results received through direct and indirect (through target texture) rendering of text." );


    CText text;
    REQUIRE_NOTHROW( text = CText( loadFontResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/fonts/arial.ttf" ), 32 ) );
    text.append( L"This is an example text.\n" );
    text.append( L"Remember how it looks!", EFontStyle::BOLD, vec3f{ 1.f, 0.f, 0.f } );
    text.generateData();

    window->clear();
        textRenderer.bindShader();
        textRenderer.clear();
        textRenderer.submitText( text, vec2f{ 50.f, 50.f } );
        textRenderer.render( window->getFramebuffer() );
    window->flipBuffer();

    showInfoMessageBox( testName, "This is a text rendered directly onto screen." );


    CTexture2D blank;
    REQUIRE_NOTHROW( blank = CTexture2D( loadTexture2DResourceFromPixels( nullptr, window->getSizeWidth(), window->getSizeHeight(), GL_RGBA, false ) ) );
    CFramebuffer blankFramebuffer( blank );
    blankFramebuffer.setClearColor( vec4f( 0.f ) ); 

    window->clear();
        blankFramebuffer.bind();
        textRenderer.bindShader();
        textRenderer.render( blankFramebuffer ); // retains the render data from previous pass

        spriteRenderer.bindShader();
        spriteRenderer.submitSprite( blank, vec2f( 0.f ) );
        spriteRenderer.render( window->getFramebuffer() );
    window->flipBuffer();

    showInfoMessageBox( testName, "This is a text rendered first onto a sprite and then that sprite is rendered onto screen." );


    REQUIRE( showConfirmMessageBox( testName ) );


    chestnutQuit();
}