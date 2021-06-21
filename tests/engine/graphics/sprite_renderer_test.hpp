#ifndef __CHESTNUT_SPRITE_RENDERER_TEST_H__
#define __CHESTNUT_SPRITE_RENDERER_TEST_H__

#include "engine/main/window.hpp"
#include "engine/resources/shader_program_resource.hpp"
#include "engine/resources/texture2d_resource.hpp"
#include "engine/graphics/sprite_renderer.hpp"

#include <cassert>

namespace chestnut
{
namespace test
{
    void spriteRendererTest()
    {
        CWindow window;

        assert( window.create( windowPropertiesDefault( 3, 3 ), "Sprite render test", 800, 600, 600, 400 ) );

        CShaderProgram shader( loadShaderProgramResourceFromFiles( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
        CSpriteRenderer renderer = CSpriteRenderer( shader );
        auto texResource = loadTexture2DResourceFromFile( "../assets/images/awesomeface.png" );
        assert( texResource->isValid() );

        CTexture2D tex1( texResource );
        CTexture2D tex2( texResource ); tex2.setClippingRect( {256, 256, 256, 256} ); tex2.setTint( { 1.f, 0.f, 0.f } ); tex2.setTintFactor( 0.4f );
        CTexture2D tex3( texResource ); tex3.setClippingRect( {256, 256, 256, 256} ); tex3.setTint( { 1.f, 0.f, 0.f } ); tex3.setTintFactor( 0.8f );


        CAutoTimer timer = CAutoTimer(0);

        renderer.bindShader();
        renderer.setViewMatrix( mat4f() );
        renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

        timer.start();
        while( timer.getCurrentTimeInSeconds() < 5 )
        {
            if( timer.tick() )
            {
                window.clear();
                    renderer.clear();
                    renderer.submitSprite( tex1, {0,0}, {0,0}, {0.1, 0.1} );
                    renderer.submitSprite( tex2, {200,200}, {0.5,0.5}, {0.2, 0.2} );
                    renderer.submitSprite( tex3, {400,400}, {0.5,0.5}, {1, 1}, CHESTNUT_PI/2 );
                    renderer.render();
                window.flipBuffer();

                window.setTitle( "Sprite render test - " + std::to_string( timer.getAvgUpdatesPerSec() ) );
            }
        }
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_TEST_H__