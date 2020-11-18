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
        void setClippingRect( Vector2i position, Vector2i dimensions );
        void setPosition( float x, float y );
        void setPosition( Vector2f position );
        void setScale( float sx, float sy );
        void setScale( Vector2f scale );
        void setDimensionsDirectly( float w, float h );
        void setDimensionsDirectly( Vector2f dimensions );
        void setRotation( float angleDeg );
        void setRotation( Vector2f rotation );
        void setRotationPoint( float rx, float ry );
        void setRotationPoint( Vector2f rotPoint );
        void setRotationPointToCenter();
        void setFlip( SDL_RendererFlip flip );

        void draw() const;
        void draw( float x, float y ) const;
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE_H__
