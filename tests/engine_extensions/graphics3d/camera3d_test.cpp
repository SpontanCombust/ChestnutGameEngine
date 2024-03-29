#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/constants.hpp"
#include "../src/chestnut/engine/macros.hpp"
#include "../src/chestnut/engine/maths/angles.hpp"
#include "../src/chestnut/engine/misc/auto_timer.hpp"
#include "../src/chestnut/engine_extensions/graphics3d/graphics/renderers/plain_mesh_renderer.hpp"
#include "../src/chestnut/engine_extensions/graphics3d/graphics/camera3d.hpp"

#include <SDL.h>


using namespace chestnut::engine;

TEST_CASE( "3D camera test", "[manual][demo]" )
{
    const char *testName = "3D camera test";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );
    window.toggleVsync(true);

    CPlainMeshRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );

    CMesh mesh;
    REQUIRE_NOTHROW( mesh = CMesh( CMeshResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/models/suzanne.obj" ).value() ) );

    CTexture2D textureDiffuse;
    REQUIRE_NOTHROW( textureDiffuse = CTexture2D( CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/marble.png" ).value() ) );
    mesh.getResource()->m_material.diffuse = textureDiffuse;

    CCamera3D camera;
    camera.setPosition( {0.f, 0.f, 5.f} );
    camera.calcViewFromLookAt( {0.f, 0.f, 0.f} );
    SDL_SetRelativeMouseMode(SDL_TRUE); //TODO hideAndConstrainCursor method in CWindow
    const float MOUSE_MOVE_SENSITIVITY = 10.f;
    const float MOUSE_WHEEL_SENSITIVITY = 40.f;
    const float MOVEMENT_SPEED = 5.f;

    showInfoMessageBox( testName, 
        "w/a/s/d            - movement\n"
        "mouse motion       - rotation\n"
        "left mouse button  - face the object\n" 
        "mouse wheel        - change FOV\n" 
    );

    SDL_Event e;
    bool running = true;
    CAutoTimer timer(0);
    timer.start();
    while(running)
    {
        timer.tick();

        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_w:
                    camera.setPosition( camera.getPosition() + camera.getDirection() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_s:
                    camera.setPosition( camera.getPosition() - camera.getDirection() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_a:
                    camera.setPosition( camera.getPosition() - camera.getRight() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_d:
                    camera.setPosition( camera.getPosition() + camera.getRight() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                }
            }
            else if(e.type == SDL_MOUSEMOTION)
            {
                camera.setYaw( camera.getRotation().yaw + (float)e.motion.xrel * MOUSE_MOVE_SENSITIVITY * timer.getDeltaTime() );
                camera.setPitch( camera.getRotation().pitch - (float)e.motion.yrel * MOUSE_MOVE_SENSITIVITY * timer.getDeltaTime() );
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    camera.calcViewFromLookAt(vec3f(0.f, 0.f, 0.f));
                }
            }
            else if(e.type == SDL_MOUSEWHEEL)
            {
                camera.setFOV( camera.getFOV() - (float)e.wheel.y * MOUSE_WHEEL_SENSITIVITY * timer.getDeltaTime() );
            }
        }

        camera.calcViewFromRotation();
        camera.calcProjection();

        renderer.setProjectionMatrix(camera.getProjectionMatrix());
        renderer.setViewMatrix(camera.getViewMatrix());

        window.clear();
            renderer.clear();
            renderer.submitMesh(mesh, {0.f, 0.f, 0.f});
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();
    }


    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
    sleepFor(1000);
}







/*
#include "../src/chestnut/engine/graphics/algorithms/heightmap.hpp"
#include "../src/chestnut/engine/graphics/renderers/phong_renderer.hpp"

TEST_CASE( "3D camera test - heightmap", "[manual][demo]" )
{
    const char *testName = "3D camera test";

    chestnutInit();

    CWindow window( testName );
    REQUIRE( window.isValid() );
    window.toggleVsync(true);

    CPhongRenderer renderer;
    REQUIRE_NOTHROW( renderer.init() );

    std::shared_ptr<SHeightmap> heightmap;
    REQUIRE_NOTHROW(heightmap = heightmapFromFile("/home/spontan/Pobrane/heightmap.png", 3.f).value());
    std::shared_ptr<CMeshDataResource> heightmapMeshData;
    REQUIRE_NOTHROW(heightmapMeshData = meshDataFromHeightmap(*heightmap, {10.f, 10.f}).value());

    CMesh mesh;
    REQUIRE_NOTHROW( mesh = CMesh(heightmapMeshData, SMaterial{}) );

    CTexture2D textureDiffuse;
    REQUIRE_NOTHROW( textureDiffuse = CTexture2D( CTexture2DResource::loadFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/images/marble.png" ).value() ) );
    mesh.getResource()->m_material.diffuse = textureDiffuse;

    CDirectionalLight light;
    light.m_direction = {1.f, -1.f, 0.f};
    light.m_ambient = {0.1f, 0.1f, 0.1f};
    light.m_diffuse = {0.8f, 0.8f, 0.8f};
    light.m_specular = {0.8f, 0.8f, 0.8f};

    CCamera3D camera;
    camera.setPosition( {0.f, 0.f, 5.f} );
    camera.calcViewFromLookAt( {0.f, 0.f, 0.f} );
    SDL_SetRelativeMouseMode(SDL_TRUE); //TODO hideAndConstrainCursor method in CWindow
    const float MOUSE_MOVE_SENSITIVITY = 10.f;
    const float MOUSE_WHEEL_SENSITIVITY = 40.f;
    const float MOVEMENT_SPEED = 5.f;

    showInfoMessageBox( testName, 
        "w/a/s/d            - movement\n"
        "mouse motion       - rotation\n"
        "left mouse button  - face the object\n" 
        "mouse wheel        - change FOV\n" 
    );

    SDL_Event e;
    bool running = true;
    CAutoTimer timer(0);
    timer.start();
    while(running)
    {
        timer.tick();

        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_w:
                    camera.setPosition( camera.getPosition() + camera.getDirection() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_s:
                    camera.setPosition( camera.getPosition() - camera.getDirection() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_a:
                    camera.setPosition( camera.getPosition() - camera.getRight() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                case SDLK_d:
                    camera.setPosition( camera.getPosition() + camera.getRight() * MOVEMENT_SPEED * timer.getDeltaTime() );
                    break;
                }
            }
            else if(e.type == SDL_MOUSEMOTION)
            {
                camera.setYaw( camera.getRotation().yaw + (float)e.motion.xrel * MOUSE_MOVE_SENSITIVITY * timer.getDeltaTime() );
                camera.setPitch( camera.getRotation().pitch - (float)e.motion.yrel * MOUSE_MOVE_SENSITIVITY * timer.getDeltaTime() );
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    camera.calcViewFromLookAt(vec3f(0.f, 0.f, 0.f));
                }
            }
            else if(e.type == SDL_MOUSEWHEEL)
            {
                camera.setFOV( camera.getFOV() - (float)e.wheel.y * MOUSE_WHEEL_SENSITIVITY * timer.getDeltaTime() );
            }
        }

        camera.calcViewFromRotation();
        camera.calcProjection();

        renderer.setProjectionMatrix(camera.getProjectionMatrix());
        renderer.setViewMatrix(camera.getViewMatrix());

        window.clear();
            renderer.clear();
            renderer.submitMesh(mesh, {0.f, 0.f, 0.f});
            renderer.submitLight(light);
            renderer.render( window.getFramebuffer() );
        window.flipBuffer();
    }


    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
    sleepFor(1000);
}
*/
