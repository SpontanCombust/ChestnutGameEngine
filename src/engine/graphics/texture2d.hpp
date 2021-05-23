#ifndef __CHESTNUT_TEXTURE2D_H__
#define __CHESTNUT_TEXTURE2D_H__

#include "engine/resources/texture2d_resource.hpp"
#include "engine/maths/rectangle.hpp"

namespace chestnut
{
    class CTexture2D
    {
    private:
        std::shared_ptr<CTexture2DResource> m_texResource;

        SRectangle m_clipRect;

    public:
        CTexture2D() = default;
        CTexture2D( std::shared_ptr<CTexture2DResource> resource );

        unsigned int getID() const;
        bool isValid() const;

        void bind() const;
        void unbind() const;

        unsigned int getPixelFormat() const;
        int getWidth() const;
        int getHeight() const;

        // Coordinates and dimensions in pixels
        SRectangle getClippingRect() const;
        // Coordinates and dimensions in pixels
        void setClippingRect( const SRectangle& rect );

        void setFiltering( int minifyingFilter, int magnifyingFilter );

        void setWrapping( int wrapS, int wrapT );
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE2D_H__
