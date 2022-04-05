#include "init.hpp"

#include "debug/log.hpp"
#include "resources/resource_manager.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


namespace chestnut::engine
{
    bool wasInit = false;

    bool chestnutInit( int glVerMajor, int glVerMinor, bool glAllowOnlyCoreProfile )
    {
        int flags;


        flags = SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_AUDIO;
        if( SDL_Init( flags ) < 0 )
        {
            LOG_ERROR( "SDL failed to initialize! " << SDL_GetError() );
            return false;
        }


        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG_ERROR( "SDL_image failed to initialize!" << IMG_GetError() );
            SDL_Quit();
            return false;
        }


        if( TTF_Init() < 0 )
        {
            LOG_ERROR( "SDL_ttf failed to initialize!" << TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
            return false;
        }


        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            LOG_ERROR( "SDL_mixer failed to initialize!" << Mix_GetError() );
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return false;
        }


        if( SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, glVerMajor ) < 0 )
        {
            LOG_WARNING( "Failed to set OpenGL major version!" );
            LOG_WARNING( TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
            return false;
        }
        if( SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, glVerMinor ) < 0 )
        {
            LOG_WARNING( "Failed to set OpenGL minor version!" );
            LOG_WARNING( TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
            return false;
        }

        if( glAllowOnlyCoreProfile )
        {
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        }
        else
        {
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
        }
        

        wasInit = true;

        return true;
    }

    bool chestnutWasInit() 
    {
        return wasInit;
    }

    void chestnutQuit()
    {
        // When you delete the current OpenGL context, create a new one and then try to GET a resource
        // it will give you a resource associated with the previous context, because it was not freed.
        // In order to prevent this we have to free all the resources that are associated with
        // the current context when we delete said context. It should be done in the window class,
        // as that's where the context is created, but this will do for now as I don't intend this engine to work
        // with multiple windows (and with that multiple OpenGL contexts).
        CResourceManager::freeAllResources();

        if( wasInit )
        {
            Mix_CloseAudio();
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();

            wasInit = false;
        }
    }

} // namespace chestnut::engine
