#include "texture2d.hpp"

namespace chestnut::engine 
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
        
        m_clipRect = { 0.f, 0.f, (float)resource->m_width, (float)resource->m_height };
        m_tint = { 1.f, 1.f, 1.f };
        m_tintFactor = 0.f;
    }

    const std::shared_ptr<CTexture2DResource>& CTexture2D::getResource() const
    {
        return m_texResource;
    }

    GLuint CTexture2D::getID() const
    {
        return m_texResource ? m_texResource->m_texID : 0;
    }
    
    bool CTexture2D::isValid() const
    {
        return m_texResource && m_texResource->m_texID != 0;
    }
    
    void CTexture2D::bind() const
    {
        if( m_texResource )
        {
            glBindTexture( GL_TEXTURE_2D, m_texResource->m_texID );
        }
        else
        {
            glBindTexture( GL_TEXTURE_2D, 0 );
        }
    }

    void CTexture2D::unbind() const
    {
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    GLenum CTexture2D::getPixelFormat() const
    {
        return m_texResource ? m_texResource->m_pixelFormat : 0;
    }

    int CTexture2D::getWidth() const
    {
        return m_texResource ? m_texResource->m_width : 0;
    }

    int CTexture2D::getHeight() const
    {
        return m_texResource ? m_texResource->m_height : 0;
    }

    vec2i CTexture2D::getSize() const
    {
        return m_texResource ? vec2i{ m_texResource->m_width, m_texResource->m_height } : vec2i{ 0, 0 };
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
        bind();
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifyingFilter );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyingFilter );
    }

    void CTexture2D::setWrapping( GLint wrapS, GLint wrapT )
    {
        bind();
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
    }

} // namespace chestnut::engine