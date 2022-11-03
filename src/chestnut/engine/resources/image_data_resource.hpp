#ifndef __CHESTNUT_ENGINE_IMAGE_DATA_RESOUCE_H__
#define __CHESTNUT_ENGINE_IMAGE_DATA_RESOUCE_H__

#include "chestnut/engine/macros.hpp"
#include "resource.hpp"

#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include <string>


namespace chestnut::engine
{
    class CHESTNUT_API CImageDataResource : public IResource
    {
    public:
        tl::optional<std::string> m_sourcePath;

        unsigned char *m_data;
        int m_width, m_height;
        int m_numChannels;


    public:
        CImageDataResource() noexcept;
        ~CImageDataResource() noexcept;

        static tl::expected<std::shared_ptr<CImageDataResource>, const char *> loadFromFile(const char *imagePath, bool flipVertically) noexcept;
        // pixelData can be null if you want to only allocate the memory for the image data
        static tl::expected<std::shared_ptr<CImageDataResource>, const char *> loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_IMAGE_DATA_RESOUCE_H__