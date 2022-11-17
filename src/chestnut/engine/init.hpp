#pragma once


#include "chestnut/engine/macros.hpp"

namespace chestnut::engine
{
    // Initializes SDL2 library and its sublibraries
    // Returns false of failure
    // To configure more aspects of how OpenGL will behave use SDL_GL_SetAttribute()
    // See https://wiki.libsdl.org/SDL_GL_SetAttribute
    bool CHESTNUT_API chestnutInit( int glVerMajor = 3, int glVerMinor = 3, bool glAllowOnlyCoreProfile = false );

    bool CHESTNUT_API chestnutWasInit();

    void CHESTNUT_API chestnutQuit();

} // namespace chestnut::engine

