#include "init.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "debug/log.hpp"

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
