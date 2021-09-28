#ifndef __CHESTNUT_ENGINE_INIT_H__
#define __CHESTNUT_ENGINE_INIT_H__

namespace chestnut
{
    // Initializes SDL2 library and its sublibraries
    // Returns false of failure
    // To configure more aspects of how OpenGL will behave use SDL_GL_SetAttribute()
    // See https://wiki.libsdl.org/SDL_GL_SetAttribute
    bool chestnutInit( int glVerMajor = 3, int glVerMinor = 3, bool glAllowOnlyCoreProfile = false );

    bool chestnutWasInit();

    void chestnutQuit();

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_INIT_H__