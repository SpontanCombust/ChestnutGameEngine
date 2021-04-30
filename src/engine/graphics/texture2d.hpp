#ifndef __CHESTNUT_TEXTURE2D_H__
#define __CHESTNUT_TEXTURE2D_H__

#include "engine/maths/rectangle.hpp"

namespace chestnut
{
    class CTexture2D
    {
    private:
        unsigned int m_texID;

        unsigned int m_pixelFormat;
        int m_width, m_height;

        SRectangle m_clipRect;

    public:
        CTexture2D();
        CTexture2D( unsigned int texID, int width, int height, unsigned int pixelFormat );
        ~CTexture2D() = default;

        unsigned int getID() const;
        bool isValid() const;

        void bind();
        void unbind();

        unsigned int getPixelFormat() const;
        int getWidth() const;
        int getHeight() const;

        SRectangle getClippingRect();
        void setClippingRect( SRectangle rect );

        void setFiltering( int minifyingFilter, int magnifyingFilter );

        void setWrapping( int wrapS, int wrapT );
    };   

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE2D_H__
