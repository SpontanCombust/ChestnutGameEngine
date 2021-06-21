#ifndef __CHESTNUT_TEXTURE2D_H__
#define __CHESTNUT_TEXTURE2D_H__

#include "engine/resources/texture2d_resource.hpp"
#include "engine/maths/rectangle.hpp"

namespace chestnut
{
    class CTexture2D
    {
    protected:
        std::shared_ptr<CTexture2DResource> m_texResource;

        SRectangle m_clipRect;

    public:
        CTexture2D() = default;
        CTexture2D( std::shared_ptr<CTexture2DResource> resource );

        GLuint getID() const;
        bool isValid() const;

        void bind() const;
        void unbind() const;

        GLenum getPixelFormat() const;
        int getWidth() const;
        int getHeight() const;

        // Coordinates and dimensions in pixels
        SRectangle getClippingRect() const;
        // Coordinates and dimensions in pixels
        void setClippingRect( const SRectangle& rect );

        void setFiltering( GLint minifyingFilter, GLint magnifyingFilter );

        void setWrapping( GLint wrapS, GLint wrapT );
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE2D_H__
