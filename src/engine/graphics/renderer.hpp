#ifndef __CHESTNUT_RENDERER_H__
#define __CHESTNUT_RENDERER_H__

#include "texture.hpp"

#include <SDL2/SDL.h>

namespace chestnut
{
    class CRenderer
    {
    private:
        static SDL_Renderer *m_sdlRenderer;

    public:
        static void setSDLRenderer( SDL_Renderer *renderer );
        static SDL_Renderer *getSDLRenderer();

        // Throws an exception if pointer to SDL_Texture in texture is null
        static void renderTexture( const CTexture& texture );

        static void renderPresent();
        static void renderClear();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERER_H__