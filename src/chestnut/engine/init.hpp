#pragma once


namespace chestnut::engine
{
    // Initializes SDL2 library and its sublibraries
    // Returns false of failure
    // To configure more aspects of how OpenGL will behave use SDL_GL_SetAttribute()
    // See https://wiki.libsdl.org/SDL_GL_SetAttribute
    bool __declspec(dllexport) chestnutInit( int glVerMajor = 3, int glVerMinor = 3, bool glAllowOnlyCoreProfile = false );

    bool __declspec(dllexport) chestnutWasInit();

    void __declspec(dllexport) chestnutQuit();

} // namespace chestnut::engine

