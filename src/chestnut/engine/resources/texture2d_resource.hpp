#ifndef __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__

#include "resource.hpp"
#include "image_data_resource.hpp"

#include <GL/glew.h>
#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include <string>


namespace chestnut::engine
{
    // A texture resource class that provides automatic texture deallocation on object deletion
    class CTexture2DResource : public IResource
    {
    public:
        tl::optional<std::string> m_texturePath;

        GLuint m_texID;
        GLenum m_pixelFormat;
        int m_width, m_height;

    public:
        CTexture2DResource() noexcept;
        ~CTexture2DResource() noexcept;

        static tl::expected<std::shared_ptr<CTexture2DResource>, const char *> loadFromImageData(std::shared_ptr<CImageDataResource> imageData) noexcept;
        // pixelData can be null if you want to only create a blank texture
        static tl::expected<std::shared_ptr<CTexture2DResource>, const char *> loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept;
        static tl::expected<std::shared_ptr<CTexture2DResource>, const char *> loadFromFile(const char *texturePath) noexcept;
    };



} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TEXTURE2D_RESOURCE_H__