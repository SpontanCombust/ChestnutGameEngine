#ifndef __CHESTNUT_ENGINE_SPRITE_H__
#define __CHESTNUT_ENGINE_SPRITE_H__

#include "chestnut/engine/macros.hpp"
#include "opengl/texture2d.hpp"
#include "../maths/rectangle.hpp"
#include "../maths/vector2.hpp"
#include "../maths/vector3.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CSprite : public CTexture2D
    {
    protected:
        SRectangle m_clipRect;
        vec3f m_tint;
        float m_tintFactor;

    public:
        CSprite();
        explicit CSprite(std::shared_ptr<CTexture2DResource> resource);
        explicit CSprite(std::shared_ptr<CImageDataResource> resource);

        // Coordinates and dimensions in pixels
        SRectangle getClippingRect() const;
        // Coordinates and dimensions in pixels
        void setClippingRect( const SRectangle& rect );

        const vec3f& getTint() const;
        void setTint( const vec3f& tint );

        float getTintFactor() const;
        void setTintFactor( float factor );
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SPRITE_H__