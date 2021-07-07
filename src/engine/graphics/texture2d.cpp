#include "texture2d.hpp"

#include "engine/libs.hpp"

namespace chestnut 
{
    CTexture2D::CTexture2D() 
    {
        m_clipRect = { 0, 0, 0, 0 };
        m_tint = { 1.f, 1.f, 1.f };
        m_tintFactor = 0.f;
    }

    CTexture2D::CTexture2D( std::shared_ptr<CTexture2DResource> resource ) 
    {
        m_texResource = resource;
        
        m_clipRect = { 0.f, 0.f, (float)resource->width, (float)resource->height };
        m_tint = { 1.f, 1.f, 1.f };
        m_tintFactor = 0.f;
    }

    const std::shared_ptr<CTexture2DResource>& CTexture2D::getResource() const
    {
        return m_texResource;
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

    vec2i CTexture2D::getSize() const
    {
        return { m_texResource->width, m_texResource->height };
    }

    SRectangle CTexture2D::getClippingRect() const
    {
        return m_clipRect;
    }

    void CTexture2D::setClippingRect( const SRectangle& rect ) 
    {
        m_clipRect = rect;
    }

    const vec3f& CTexture2D::getTint() const
    {
        return m_tint;
    }

    void CTexture2D::setTint( const vec3f& tint ) 
    {
        m_tint = tint;
    }

    float CTexture2D::getTintFactor() const
    {
        return m_tintFactor;
    }

    void CTexture2D::setTintFactor( float factor ) 
    {
        m_tintFactor = factor;
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