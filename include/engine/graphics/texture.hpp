#ifndef __CHESTNUT_TEXTURE_H__
#define __CHESTNUT_TEXTURE_H__

#include "texture_resource.hpp"
#include "engine/core/vector.hpp"

#include <SDL_image.h>

namespace chestnut
{
    class CTextureResource; //forward declaration

    class CTexture
    {
    private:
        SDL_Texture *m_sdlTexture;
        bool m_isResourceInstance;

        SDL_Rect m_srcRect;
        SDL_FRect m_dstRect;
        float m_angleDeg;
        SDL_FPoint m_rotPoint;
        SDL_RendererFlip m_flip;

    public:
        CTexture( int w, int h );
        CTexture( const CTextureResource *textureResource );
        ~CTexture();

        void setClippingRect( int x, int y, int w, int h );
        void setScale( float sx, float sy );
        void setRotation( float angleDeg );
        void setRotationPoint( float rx, float ry );
        void setFlip( SDL_RendererFlip flip );

        void render( float x, float y );
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE_H__
