#ifndef __CHESTNUT_TEXTURE2D_H__
#define __CHESTNUT_TEXTURE2D_H__

#include "engine/resources/texture2d_resource.hpp"
#include "engine/maths/rectangle.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/vector3.hpp"

namespace chestnut
{
    class CTexture2D
    {
    protected:
        std::shared_ptr<CTexture2DResource> m_texResource;

        SRectangle m_clipRect;
        vec3f m_tint;
        float m_tintFactor;

    public:
        CTexture2D();
        CTexture2D( std::shared_ptr<CTexture2DResource> resource );

        const std::shared_ptr<CTexture2DResource>& getResource() const;

        GLuint getID() const;

        bool isValid() const;

        void bind() const;
        void unbind() const;

        GLenum getPixelFormat() const;
        int getWidth() const;
        int getHeight() const;
        vec2i getSize() const;

        // Coordinates and dimensions in pixels
        SRectangle getClippingRect() const;
        // Coordinates and dimensions in pixels
        void setClippingRect( const SRectangle& rect );

        const vec3f& getTint() const;
        void setTint( const vec3f& tint );

        float getTintFactor() const;
        void setTintFactor( float factor );

        void setFiltering( GLint minifyingFilter, GLint magnifyingFilter );

        void setWrapping( GLint wrapS, GLint wrapT );
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE2D_H__
