#ifndef __CHESTNUT_TEXTURE2D_RESOURCE_H__
#define __CHESTNUT_TEXTURE2D_RESOURCE_H__

#include "engine/libs.hpp"

#include <memory>
#include <string>

namespace chestnut
{
    // A texture resource class that provides automatic texture deallocation on object deletion
    class CTexture2DResource
    {
    public:
        GLuint texID;
        GLenum pixelFormat;
        int width, height;

        CTexture2DResource();
        CTexture2DResource( GLuint texID, GLenum pixelFormat, int width, int height );

        ~CTexture2DResource();

        bool isValid() const;
    };

    // Throws exception if fails to load the texture
    std::shared_ptr< CTexture2DResource > loadTextureResourceFromPixels( void *pixels, int width, int height, unsigned int pixelFormat );
    // Throws exception if fails to load the texture
    std::shared_ptr< CTexture2DResource > loadTextureResourceFromFile( const std::string& path );

} // namespace chestnut

#endif // __CHESTNUT_TEXTURE2D_RESOURCE_H__