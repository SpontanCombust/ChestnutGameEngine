#include "texture2d.hpp"

#include "engine/libs.hpp"

namespace chestnut 
{
    CTexture2D::CTexture2D() 
    {
        m_texID = 0;
        m_width = 0;
        m_height = 0;
        m_pixelFormat = 0;
    }

    CTexture2D::CTexture2D( unsigned int texID, int width, int height, unsigned int pixelFormat ) 
    {
        m_texID = texID;
        m_width = width;
        m_height = height;
        m_pixelFormat = pixelFormat;
        m_clipRect = SRectangle( 0.f, 0.f, m_width, m_height );
    }

    unsigned int CTexture2D::getID() const
    {
        return m_texID;
    }
    
    bool CTexture2D::isValid() const
    {
        return m_texID != 0;
    }
    
    void CTexture2D::bind() 
    {
        glBindTexture( GL_TEXTURE_2D, m_texID );
    }

    void CTexture2D::unbind() 
    {
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    unsigned int CTexture2D::getPixelFormat() const
    {
        return m_pixelFormat;
    }

    int CTexture2D::getWidth() const
    {
        return m_width;
    }

    int CTexture2D::getHeight() const
    {
        return m_height;
    }

    SRectangle CTexture2D::getClippingRect() 
    {
        return m_clipRect;
    }

    void CTexture2D::setClippingRect( SRectangle rect ) 
    {
        m_clipRect = rect;
    }

    void CTexture2D::setFiltering( int minifyingFilter, int magnifyingFilter ) 
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifyingFilter );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyingFilter );
    }

    void CTexture2D::setWrapping( int wrapS, int wrapT )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
    }

} // namespace chestnut