#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/resources/font_resource.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/shader_program.hpp"
#include "../src/chestnut/engine/graphics/sprite_renderer.hpp"
#include "../src/chestnut/engine/graphics/text_renderer.hpp"


using namespace chestnut;

TEST_CASE( "Text renderer test - font style sheets", "[interactive]" )
{
    chestnutInit();

    const char *testName = "Text test - font style sheets";

    std::shared_ptr< CFontResource > fontResource;
    REQUIRE_NOTHROW( fontResource = loadFontResourceFromFile( "../assets/fonts/arial.ttf" ) );  
    REQUIRE( fontResource );

    std::shared_ptr< CWindow > window = createWindow( testName );
    REQUIRE( window );

    CShaderProgram textureShader( loadShaderProgramResourceFromFiles( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
    CSpriteRenderer spriteRenderer;
    spriteRenderer.init( textureShader );

    spriteRenderer.bindShader();
    spriteRenderer.setViewMatrix( mat4f() );
    spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SECTION( "Normal font" )
    {
        const auto& normalSheet = fontResource->getConfig( 32, EFontStyle::NORMAL ).textureResource;

        showRunTestMessageBox( testName, "Click to render a sheet with regular font" );

        window->clear();
            spriteRenderer.clear();
            spriteRenderer.submitSprite( CTexture2D( normalSheet ), { 0.f, 0.f } );
            spriteRenderer.render();
        window->flipBuffer();

        showConfirmTestMessageBox( testName );
    }

    SECTION( "Bold font" )
    {
        const auto& boldSheet = fontResource->getConfig( 32, EFontStyle::BOLD ).textureResource;

        showRunTestMessageBox( testName, "Click to render a sheet with bold font" );

        window->clear();
            spriteRenderer.clear();
            spriteRenderer.submitSprite( CTexture2D( boldSheet ), { 0.f, 0.f } );
            spriteRenderer.render();
        window->flipBuffer();

        showConfirmTestMessageBox( testName );
    }

    SECTION( "Italic font" )
    {
        const auto& italicSheet = fontResource->getConfig( 32, EFontStyle::ITALIC ).textureResource;

        showRunTestMessageBox( testName, "Click to render a sheet with italic font" );

        window->clear();
            spriteRenderer.clear();
            spriteRenderer.submitSprite( CTexture2D( italicSheet ), { 0.f, 0.f } );
            spriteRenderer.render();
        window->flipBuffer();

        showConfirmTestMessageBox( testName );
    }
        
    SECTION( "Underline strikethrough font" )
    {
        const auto& underlineStrikethroughSheet = fontResource->getConfig( 32, EFontStyle::UNDERLINE | EFontStyle::STRIKETHROUGH ).textureResource;

        showRunTestMessageBox( testName, "Click to render a sheet with underline strikethrough font" );

        window->clear();
            spriteRenderer.clear();
            spriteRenderer.submitSprite( CTexture2D( underlineStrikethroughSheet ), { 0.f, 0.f } );
            spriteRenderer.render();
        window->flipBuffer();

        showConfirmTestMessageBox( testName );
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Text renderer test - rendering text glyphs", "[interactive]" )
{
    chestnutInit();

    const char *testName = "Text test - rendering text glyphs";

    std::shared_ptr< CFontResource > fontResource;
    REQUIRE_NOTHROW( fontResource = loadFontResourceFromFile( "../assets/fonts/arial.ttf" ) );  
    REQUIRE( fontResource );

    std::shared_ptr< CWindow > window = createWindow( testName );
    REQUIRE( window );

    CShaderProgram textShader( loadShaderProgramResourceFromFiles( "../assets/shaders/text.vert", "../assets/shaders/text.frag" ) );
    CTextRenderer textRenderer;
    textRenderer.init( textShader );

    textRenderer.bindShader();
    textRenderer.setViewMatrix( mat4f() );
    textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    CText text = CText( fontResource, 32 );
    text.setAligment( ETextAlignment::CENTER );
    text.append( L"Wlazł ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( L"kotek\n", EFontStyle::BOLD, { 1.f, 1.f, 0.0 } );
    text.append( L"na ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( L"płotek.", EFontStyle::ITALIC, { 0.f, 1.f, 0.f } );
    text.newline();
    text.append( L"Pierdolnął go\n", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( L"młotek.", EFontStyle::UNDERLINE, { 1.f, 0.f, 0.f } );


    showRunTestMessageBox( testName, "Click to render some text" );

    window->clear();
        textRenderer.clear();

        text.generateData();
        textRenderer.submitText( text, { 50.f, 50.f } );

        text.setAligment( ETextAlignment::RIGHT );
        text.setLineSpacing( 1.5f );
        text.setMaxWidthPixels( 100 );
        text.generateData();
        textRenderer.submitText( text, { 650.f, 50.f }, { 1.5f, 1.5f } );

        textRenderer.render();
    window->flipBuffer();

    showConfirmTestMessageBox( testName );


    chestnutQuit();
    sleepFor(1000);    
}

