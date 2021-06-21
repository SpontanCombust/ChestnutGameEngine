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
        CTexture2D tex( loadTexture2DResourceFromFile( "../assets/images/awesomeface.png" ) );
        CTexture2D texClipped = tex; texClipped.setClippingRect( {256, 256, 256, 256} );
        assert( tex.isValid() );
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
                    renderer.submitSprite( tex, {0,0}, {0,0}, {0.1, 0.1} );
                    renderer.submitSprite( tex, {200,200}, {0.5,0.5}, {0.2, 0.2} );
                    renderer.submitSprite( texClipped, {400,400}, {0.5,0.5}, {1, 1}, CHESTNUT_PI/2 );
                    renderer.render();
                window.flipBuffer();

                window.setTitle( "Sprite render test - " + std::to_string( timer.getAvgUpdatesPerSec() ) );
            }
        }
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_TEST_H__