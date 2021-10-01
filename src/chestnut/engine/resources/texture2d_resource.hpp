#ifndef __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__

#include "resource.hpp"

#include <GL/glew.h>

#include <memory>
#include <string>

namespace chestnut::engine
{
    // A texture resource class that provides automatic texture deallocation on object deletion
    class CTexture2DResource : public IResource
    {
    public:
        std::string m_texturePath;
        bool m_wasLoadedFromFile;

        GLuint m_texID;
        GLenum m_pixelFormat;
        int m_width, m_height;

    public:
        CTexture2DResource();

        ~CTexture2DResource();


        bool isValid() const override;
    };


    // Throws exception if fails to load the texture
    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromPixels( void *pixels, int width, int height, GLenum pixelFormat );

    // Throws exception if fails to load the texture
    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromFile( const std::string& texturePath );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__