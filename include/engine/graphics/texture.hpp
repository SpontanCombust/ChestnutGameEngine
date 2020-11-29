#ifndef __CHESTNUT_TEXTURE_H__
#define __CHESTNUT_TEXTURE_H__

#include "texture_resource.hpp"
#include "engine/maths/vector.hpp"

#include <SDL_image.h>

namespace chestnut
{
    enum class ETextureFlip { NONE, HORIZONTAL, VERTICAL };

    class CTexture
    {
    private:
        SDL_Texture *m_sdlTexture;
        bool m_isResourceInstance;

        Vector2i m_clippingRectPos;
        Vector2i m_clippingRectSize;

        Vector2f m_position;

        Vector2f m_size;
        // positive angle = rotation counter clockwise, just as with cartesian system
        float m_rotationRad;
        /*  values normally in a range <0;1> - tells in which point regardless of scale should be the rotation pivot
            examples: [0.5, 0.5] means center of a texture, [0.0, 0.0] means upper left corner etc. */
        Vector2<double> m_rotationPoint;

        ETextureFlip m_flip;

    public:
        CTexture();
        CTexture( int w, int h );
        CTexture( const CTextureResource *textureResource );
        ~CTexture();

        void setClippingRect( int x, int y, int w, int h );
        void setClippingRect( Vector2i position, Vector2i dimensions );
        const Vector2i& getClippingRectPos() const;
        const Vector2i& getClippingRectSize() const;

        void setPosition( float x, float y );
        void setPosition( Vector2f position );
        const Vector2f& getPosition() const;

        void setScale( float sx, float sy );
        void setScale( Vector2f scale );
        const Vector2f getScale() const;

        void setSizeDirectly( float w, float h );
        void setSizeDirectly( Vector2f size );
        const Vector2f& getSize() const;

        void setRotation( float angleRad );
        void setRotation( Vector2f rotationVec );
        const float& getRotationRad() const;
        const Vector2f getRotationVec() const;

        void setRotationPoint( double rx, double ry );
        void setRotationPoint( Vector2<double> rotPoint );
        void setRotationPointToCenter();
        const Vector2<double>& getRotationPoint() const;

        void setFlip( ETextureFlip flip );
        const ETextureFlip& getFlip() const;

        SDL_Texture *getSDLTexturePtr() const;
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE_H__
