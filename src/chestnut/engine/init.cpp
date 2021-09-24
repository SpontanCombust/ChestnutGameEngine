#include "init.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "debug/debug.hpp"

namespace chestnut
{
    bool wasInit = false;

    bool chestnutInit( int glVerMajor, int glVerMinor, bool glAllowOnlyCoreProfile )
    {
        int flags;

        flags = SDL_INIT_EVERYTHING;
        if( SDL_Init( flags ) < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL failed to initialize!" );
            LOG_CHANNEL( "WINDOW", SDL_GetError() );
            return false;
        }

        flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
        if( !( IMG_Init( flags ) & flags ) )
        {
            LOG_CHANNEL( "WINDOW", "SDL_image failed to initialize!" );
            LOG_CHANNEL( "WINDOW", IMG_GetError() );
            SDL_Quit();
            return false;
        }

        if( TTF_Init() < 0 )
        {
            LOG_CHANNEL( "WINDOW", "SDL_ttf failed to initialize!" );
            LOG_CHANNEL( "WINDOW", TTF_GetError() );
            IMG_Quit();
            SDL_Quit();
            return false;
        }

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, glVerMajor );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, glVerMinor );

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
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();

            wasInit = false;
        }
    }

} // namespace chestnut
