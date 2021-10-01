#ifndef __CHESTNUT_ENGINE_TEXTURE2D_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_H__

#include "../resources/texture2d_resource.hpp"
#include "../maths/rectangle.hpp"
#include "../maths/vector2.hpp"
#include "../maths/vector3.hpp"

namespace chestnut::engine
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
        explicit CTexture2D( std::shared_ptr<CTexture2DResource> resource );

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

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TEXTURE2D_H__