#ifndef __CHESTNUT_COLORED_POLYGON2D_RENDERER_TEST_H__
#define __CHESTNUT_COLORED_POLYGON2D_RENDERER_TEST_H__

#include "engine/graphics/colored_polygon2d_renderer.hpp"
#include "engine/main/window.hpp"

namespace chestnut
{
namespace test
{
    void polygonRendererTest()
    {
        CWindow window;

        if( window.create( windowPropertiesDefault( 3, 3 ), "Polygon render test", 800, 600, 600, 400 ) )
        {
            CShaderProgram shader( loadShaderProgramResourceFromFiles( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );
            CColoredPolygon2DRenderer renderer = CColoredPolygon2DRenderer( shader );
            CAutoTimer timer = CAutoTimer(0);

            renderer.bindShader();
            renderer.setViewMatrix( mat4f() );
            renderer.setProjectionMatrix( matMakeOrthographic<float>( 0, 800, 600, 0, -1, 1 ) );

            CColoredPolygon2D square;
            square.addVertex( {0,0}, 1.f, 0.f, 0.f, 1.f );
            square.addVertex( {200,0}, 0.f, 1.f, 0.f, 1.f );
            square.addVertex( {200,200}, 0.f, 0.f, 1.f, 1.f );
            square.addVertex( {0,200}, 1.f, 1.f, 1.f, 1.f );
            square.addIndices( 0, 1, 2 );
            square.addIndices( 2, 3, 0 );

            CColoredPolygon2D triangle;
            triangle.addVertex( {-50,50}, 1.f, 0.f, 0.f, 1.f );
            triangle.addVertex( {0,-50}, 0.f, 1.f, 0.f, 1.f );
            triangle.addVertex( {50,50}, 0.f, 0.f, 1.f, 1.f );
            triangle.addIndices( 0, 1, 2 );

            timer.start();
            while( timer.getCurrentTimeInSeconds() < 5 )
            {
                if( timer.tick() )
                {
                    window.clear();
                        renderer.clear();
                        renderer.submitPolygon( square, {0,0} );
                        renderer.submitPolygon( triangle, {200,200}, {0,0}, {2,2}, CHESTNUT_PI/2 );
                        renderer.render();
                    window.flipBuffer();
                }
            }
        }

    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_COLORED_POLYGON2D_RENDERER_TEST_H__