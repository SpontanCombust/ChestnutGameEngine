#include "texture2d.hpp"

#include "engine/libs.hpp"

namespace chestnut 
{
    CTexture2D::CTexture2D( std::shared_ptr<CTexture2DResource> resource ) 
    {
        m_texResource = resource;
        
        m_clipRect = SRectangle( 0.f, 0.f, resource->width, resource->height );
    }

    GLuint CTexture2D::getID() const
    {
        return m_texResource->texID;
    }
    
    bool CTexture2D::isValid() const
    {
        if( m_texResource && m_texResource->texID != 0 )
        {
            return true;
        }
        return false;
    }
    
    void CTexture2D::bind() const
    {
        glBindTexture( GL_TEXTURE_2D, m_texResource->texID );
    }

    void CTexture2D::unbind() const
    {
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    GLenum CTexture2D::getPixelFormat() const
    {
        return m_texResource->pixelFormat;
    }

    int CTexture2D::getWidth() const
    {
        return m_texResource->width;
    }

    int CTexture2D::getHeight() const
    {
        return m_texResource->height;
    }

    SRectangle CTexture2D::getClippingRect() const
    {
        return m_clipRect;
    }

    void CTexture2D::setClippingRect( const SRectangle& rect ) 
    {
        m_clipRect = rect;
    }

    void CTexture2D::setFiltering( GLint minifyingFilter, GLint magnifyingFilter ) 
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifyingFilter );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyingFilter );
    }

    void CTexture2D::setWrapping( GLint wrapS, GLint wrapT )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
    }

} // namespace chestnut