#ifndef __CHESTNUT_TEXTURE_H__
#define __CHESTNUT_TEXTURE_H__

#include "texture_resource.hpp"
#include "engine/maths/vector2.hpp"

#include <SDL_image.h>

namespace chestnut
{
    class CTexture
    {
    private:
        SDL_Texture *m_sdlTexture;
        bool m_isResourceInstance;

        vec2i m_clippingRectPos;
        vec2i m_clippingRectSize;

        vec2f m_position;

        vec2f m_size;
        // positive angle = rotation counter clockwise, just as with cartesian system
        float m_rotationRad;
        /*  values normally in a range <0;1> - tells in which point regardless of scale should be the rotation pivot
            examples: [0.5, 0.5] means center of a texture, [0.0, 0.0] means upper left corner etc. */
        vec2f m_rotationPoint;

        SDL_RendererFlip m_flip;

    public:
        CTexture();
        CTexture( int w, int h );
        CTexture( const CTextureResource *textureResource );
        ~CTexture();

        void setClippingRect( int x, int y, int w, int h );
        void setClippingRect( vec2i position, vec2i dimensions );
        const vec2i& getClippingRectPos() const;
        const vec2i& getClippingRectSize() const;

        void setPosition( float x, float y );
        void setPosition( vec2f position );
        const vec2f& getPosition() const;

        void setScale( float sx, float sy );
        void setScale( vec2f scale );
        const vec2f getScale() const;

        void setSizeDirectly( float w, float h );
        void setSizeDirectly( vec2f size );
        const vec2f& getSize() const;

        void setRotation( float angleRad );
        void setRotation( vec2f rotationVec );
        const float& getRotationRad() const;
        const vec2f getRotationVec() const;

        void setRotationPoint( float rx, float ry );
        void setRotationPoint( vec2f rotPoint );
        void setRotationPointToCenter();
        const vec2f& getRotationPoint() const;

        void setFlip( SDL_RendererFlip flip );
        const SDL_RendererFlip& getFlip() const;

        SDL_Texture *getSDLTexturePtr() const;
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE_H__
