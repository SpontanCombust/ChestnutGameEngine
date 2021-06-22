#ifndef __CHESTNUT_TEXT_RENDERER_TEST_H__
#define __CHESTNUT_TEXT_RENDERER_TEST_H__

#include "engine/main/window.hpp"
#include "engine/resources/shader_program_resource.hpp"
#include "engine/graphics/sprite_renderer.hpp"
#include "engine/resources/font_resource.hpp"
#include "engine/graphics/text_renderer.hpp"

#include <cassert>

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
            SDL_Delay( 3000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( boldSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 3000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( italicSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 3000 );

            window.clear();
                spriteRenderer.clear();
                spriteRenderer.submitSprite( underlineSheet, { 0.f, 0.f } );
                spriteRenderer.render();
            window.flipBuffer();
            SDL_Delay( 3000 );




            CShaderProgram textShader( loadShaderProgramResourceFromFiles( "../assets/shaders/text.vert", "../assets/shaders/text.frag" ) );
            CTextRenderer textRenderer;
            textRenderer.init( textShader );

            CText text1 = CText( fontResource, 32 );
            CText text2 = CText( fontResource, 33 );
            
            text1.appendString( L"Wlazł ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f, 1.f } );
            text1.appendString( L"kotek ", EFontStyle::BOLD, { 1.f, 1.f, 0.0, 1.f } );
            text1.appendString( L"na ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f, 1.f } );
            text1.appendString( L"płotek.", EFontStyle::ITALIC, { 0.f, 1.f, 0.f, 1.f } );

            text2.appendString( L"Pierdolnął go ", EFontStyle::NORMAL, { 1.f, 1.f, 1.f, 1.f } );
            text2.appendString( L"młotek.", EFontStyle::UNDERLINE, { 1.f, 0.f, 0.f, 1.f } );




            CAutoTimer timer = CAutoTimer(0);

            textRenderer.bindShader();
            textRenderer.setViewMatrix( mat4f() );
            textRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

            timer.start();
            while( timer.getCurrentTimeInSeconds() < 5 )
            {
                if( timer.tick() )
                {
                    window.clear();
                        textRenderer.clear();
                        textRenderer.submitText( text1, { 50.f, 50.f } );
                        textRenderer.submitText( text2, { 50.f, 100.f }, { 2.0f, 2.0f } );
                        textRenderer.render();
                    window.flipBuffer();
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

} // namespace test

} // namespace chestnut


#endif // __CHESTNUT_TEXT_RENDERER_TEST_H__