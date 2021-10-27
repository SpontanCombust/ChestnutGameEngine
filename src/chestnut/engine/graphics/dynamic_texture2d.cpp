#include "dynamic_texture2d.hpp"

namespace chestnut::engine
{
    CDynamicTexture2D::CDynamicTexture2D( std::shared_ptr< CDynamicTexture2DResource > resource ) 
    {
        m_texResource = resource;
    }

    const std::shared_ptr<CDynamicTexture2DResource> CDynamicTexture2D::getResourceDynamic() const
    {
        return std::dynamic_pointer_cast<CDynamicTexture2DResource>( m_texResource );
    }

    void CDynamicTexture2D::setAsRenderTarget() 
    {
        glBindFramebuffer( GL_FRAMEBUFFER, getResourceDynamic()->m_fbo );
    }

} // namespace chestnut::engine
