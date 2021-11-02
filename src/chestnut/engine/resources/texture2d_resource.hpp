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
    };


    // Throws ChestnutResourceLoadException if fails to load the texture
    // Pass pixels as null if you want to allocate pixel memory for the texture
    // pixelFormat should be one of: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA
    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromPixels( const void *pixels, int width, int height, GLenum pixelFormat, bool flipPixelsVertically );

    // texturePath - path to either JPG, PNG or TIFF image
    // Throws ChestnutResourceLoadException if fails to load the texture
    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromFile( const char *texturePath );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__