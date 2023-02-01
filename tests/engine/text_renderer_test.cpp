#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/resources/font_resource.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/graphics/opengl/shader_program.hpp"
#include "../src/chestnut/engine/graphics/renderers/sprite_renderer.hpp"
#include "../src/chestnut/engine/graphics/renderers/text_renderer.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include "test_utils.hpp"


using namespace chestnut::engine;

TEST_CASE( "Renderers - Text renderer test - font style sheets", "[manual]" )
{
    chestnutInit();

    const char *testName = "Text test - font style sheets";

    CWindow window( testName );

    std::shared_ptr< CFontResource > fontResource;
    REQUIRE_NOTHROW( fontResource = CFontResource::load( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/fonts/arial.ttf" ).value() );  

    CSpriteRenderer spriteRenderer;
    REQUIRE_NOTHROW( spriteRenderer.init() );

    spriteRenderer.setViewMatrix( mat4f() );
    spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

    SECTION( "Normal font" )
    {
        const auto& normalSheet = fontResource->getConfig( 32, EFontStyle::NORMAL ).textureResource;

        showInfoMessageBox( testName, "Click to render a sheet with regular font" );

        window.clear();
            spriteRenderer.clear();
            spriteRenderer.submitTexture( CTexture2D( normalSheet ), { 0.f, 0.f }, { 0.f, 1.f }, {1.f, -1.f} ); // y scale is negative to flip the image vertically (sprite renderer normally takes textues already flipped)
            spriteRenderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showConfirmMessageBox( testName );
    }

    SECTION( "Bold font" )
    {
        const auto& boldSheet = fontResource->getConfig( 32, EFontStyle::BOLD ).textureResource;

        showInfoMessageBox( testName, "Click to render a sheet with bold font" );

        window.clear();
            spriteRenderer.clear();
            spriteRenderer.submitTexture( CTexture2D( boldSheet ), { 0.f, 0.f }, { 0.f, 1.f }, {1.f, -1.f} ); // y scale is negative to flip the image vertically (sprite renderer normally takes textues already flipped)
            spriteRenderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showConfirmMessageBox( testName );
    }

    SECTION( "Italic font" )
    {
        const auto& italicSheet = fontResource->getConfig( 32, EFontStyle::ITALIC ).textureResource;

        showInfoMessageBox( testName, "Click to render a sheet with italic font" );

        window.clear();
            spriteRenderer.clear();
            spriteRenderer.submitTexture( CTexture2D( italicSheet ), { 0.f, 0.f }, { 0.f, 1.f }, {1.f, -1.f} ); // y scale is negative to flip the image vertically (sprite renderer normally takes textues already flipped)
            spriteRenderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showConfirmMessageBox( testName );
    }
        
    SECTION( "Underline strikethrough font" )
    {
        const auto& underlineStrikethroughSheet = fontResource->getConfig( 32, {EFontStyle::UNDERLINE, EFontStyle::STRIKETHROUGH} ).textureResource;

        showInfoMessageBox( testName, "Click to render a sheet with underline strikethrough font" );

        window.clear();
            spriteRenderer.clear();
            spriteRenderer.submitTexture( CTexture2D( underlineStrikethroughSheet ), { 0.f, 0.f }, { 0.f, 1.f }, {1.f, -1.f} ); // y scale is negative to flip the image vertically (sprite renderer normally takes textues already flipped)
            spriteRenderer.render( window.getFramebuffer() );
        window.flipBuffer();

        showConfirmMessageBox( testName );
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Renderers - Text renderer test - rendering text glyphs", "[manual]" )
{
    chestnutInit();

    const char *testName = "Text test - rendering text glyphs";

    CWindow window( testName );

    std::shared_ptr< CFontResource > fontResource;
    REQUIRE_NOTHROW( fontResource = CFontResource::load( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/testing/fonts/arial.ttf" ).value() );  
    REQUIRE( fontResource );

    CTextRenderer textRenderer;
    REQUIRE_NOTHROW( textRenderer.init() );

    textRenderer.setViewMatrix( mat4f() );
    textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );


    CText text = CText( fontResource, 32 );
    text.setAligment( ETextAlignment::CENTER );
    text.append( "Wlazł ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( "kotek\n", EFontStyle::BOLD, { 1.f, 1.f, 0.0 } );
    text.append( "na ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( "płotek.", EFontStyle::ITALIC, { 0.f, 1.f, 0.f } );
    text.newline();
    text.append( "Pierdolnął go\n", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
    text.append( "młotek.", EFontStyle::UNDERLINE, { 1.f, 0.f, 0.f } );


    showInfoMessageBox( testName, "Click to render some text" );

    window.clear();
        textRenderer.clear();

        text.generateData();
        textRenderer.submitText( text, { 50.f, 50.f } );

        text.setAligment( ETextAlignment::RIGHT );
        text.setLineSpacing( 1.5f );
        text.setMaxWidthPixels( 100 );
        text.generateData();
        textRenderer.submitText( text, { 650.f, 50.f }, { 1.5f, 1.5f } );

        textRenderer.render( window.getFramebuffer() );
    window.flipBuffer();

    REQUIRE(showConfirmMessageBox( testName ));


    chestnutQuit();
    sleepFor(1000);    
}

