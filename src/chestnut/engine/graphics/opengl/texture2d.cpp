#include "chestnut/engine/graphics/opengl/texture2d.hpp"

#include "chestnut/engine/debug/log.hpp"


namespace chestnut::engine 
{
    CTexture2D::CTexture2D( std::shared_ptr<CTexture2DResource> resource )
    : m_texResource(resource) 
    {
        
    }

    CTexture2D::CTexture2D(const std::shared_ptr<CImageDataResource>& resource) 
    {
        auto texResource = CTexture2DResource::loadFromImageData(resource);
        if(texResource) {
            m_texResource = *texResource;
        } else {
            LOG_ERROR("Failed to load texture resource from image data");
            m_texResource = nullptr;
        }
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
        if( m_texResource )
        {
            return true;
        }

        return false;
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