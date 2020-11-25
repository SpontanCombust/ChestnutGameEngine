#ifndef __CHESTNUT_TEXTURE_RESOURCE_H__
#define __CHESTNUT_TEXTURE_RESOURCE_H__

#include "engine/maths/vector.hpp"

#include <SDL2/SDL_image.h>

#include <string>

namespace chestnut 
{
    class CTextureResource
    {
    private:
        SDL_Texture *m_sdlTexture;

    public:
        CTextureResource( const std::string path );
        ~CTextureResource();

        void loadFromFile( const std::string path );
        Vector2i getSize() const;

        SDL_Texture *getSDLTexturePtr() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE_RESOURCE_H__
