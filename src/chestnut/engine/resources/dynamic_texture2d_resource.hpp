#ifndef __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_RESOURCE_H__
#define __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_RESOURCE_H__

#include "texture2d_resource.hpp"

namespace chestnut::engine
{
    // A texture resource that can be set as a render target
    class CDynamicTexture2DResource : public CTexture2DResource
    {
    public:
        GLuint m_fbo;
        GLuint m_rbo;

    public:
        CDynamicTexture2DResource();
        ~CDynamicTexture2DResource();

        bool isValid() const override;
    };


    // Throws exception if error occurs while creating the texture
    std::shared_ptr< CDynamicTexture2DResource > createDynamicTexture2DResource( int width, int height, GLenum pixelFormat );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_RESOURCE_H__