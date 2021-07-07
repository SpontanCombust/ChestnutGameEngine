#include "engine/main/window.hpp"
#include "engine/resources/shader_program_resource.hpp"
#include "engine/graphics/sprite_renderer.hpp"
#include "engine/resources/font_resource.hpp"
#include "engine/graphics/text_renderer.hpp"
#include "engine/misc/timers/auto_timer.hpp"

#include <cassert>
#include <iostream>

namespace chestnut
{
namespace test
{
    void textRendererTest()
    {
        CWindow window;

        assert( window.create( windowPropertiesDefault( 3, 3 ), "Text renderer test", 800, 600, 600, 400 ) );

        try
        {
            CShaderProgram textureShader( loadShaderProgramResourceFromFiles( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
            CSpriteRenderer spriteRenderer;
            spriteRenderer.init( textureShader );

            std::shared_ptr< CFontResource > fontResource = loadFontResourceFromFile( "../assets/fonts/arial.ttf" );  
            assert( fontResource->isValid() );



            const SFontConfig& normalConfig = fontResource->getConfig( 32, EFontStyle::NORMAL );
            const CMapSpriteSheetTexture2D<wchar_t>& normalSheet = normalConfig.glyphSpriteSheet;

            const SFontConfig& boldConfig = fontResource->getConfig( 32, EFontStyle::BOLD );
            const CMapSpriteSheetTexture2D<wchar_t>& boldSheet = boldConfig.glyphSpriteSheet;

            const SFontConfig& italicConfig = fontResource->getConfig( 33, EFontStyle::ITALIC );
            const CMapSpriteSheetTexture2D<wchar_t>& italicSheet = italicConfig.glyphSpriteSheet;

            const SFontConfig& underlineConfig = fontResource->getConfig( 33, EFontStyle::UNDERLINE );
            const CMapSpriteSheetTexture2D<wchar_t>& underlineSheet = underlineConfig.glyphSpriteSheet;



            spriteRenderer.bindShader();
            spriteRenderer.setViewMatrix( mat4f() );
            spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( normalSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 2000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( boldSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 2000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( italicSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 2000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( underlineSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 2000 );




            CShaderProgram textShader( loadShaderProgramResourceFromFiles( "../assets/shaders/text.vert", "../assets/shaders/text.frag" ) );
            CTextRenderer textRenderer;
            textRenderer.init( textShader );

            CText text = CText( fontResource, 32 );
            
            text.setAligment( ETextAlignment::CENTER );
            text.append( L"Wlazł ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
            text.append( L"kotek\n", EFontStyle::BOLD, { 1.f, 1.f, 0.0 } );
            text.append( L"na ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
            text.append( L"płotek.", EFontStyle::ITALIC, { 0.f, 1.f, 0.f } );
            text.newline();
            text.append( L"Pierdolnął go\n", EFontStyle::NORMAL, { 1.f, 1.f, 1.f } );
            text.append( L"młotek.", EFontStyle::UNDERLINE, { 1.f, 0.f, 0.f } );


            textRenderer.bindShader();
            textRenderer.setViewMatrix( mat4f() );
            textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );
            
            window.clear();
                textRenderer.clear();

                text.generateData();
                textRenderer.submitText( text, { 50.f, 50.f } );

                text.setAligment( ETextAlignment::RIGHT );
                text.setLineSpacing( 1.5f );
                text.setMaxWidthPixels( 100 );
                text.generateData();
                textRenderer.submitText( text, { 650.f, 50.f }, { 1.5f, 1.5f } );

                textRenderer.render();
            window.flipBuffer();
            SDL_Delay( 10000 );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

} // namespace test

} // namespace chestnut
