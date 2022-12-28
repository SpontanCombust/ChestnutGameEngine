#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include <string>


namespace chestnut::engine
{
    class CHESTNUT_API CImageDataResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS {
            "jpg", "jpeg", "png", "tga", "bmp", "gif"
        };

        unsigned char *m_data = nullptr;
        int m_width = 0, m_height = 0;
        int m_numChannels = 0;


    public:  
        ~CImageDataResource() noexcept;

        static tl::expected<std::shared_ptr<CImageDataResource>, std::string> 
        loadFromImageFile(std::filesystem::path imagePath, bool flipVertically) noexcept;

        // pixelData can be null if you want to only allocate the memory for the image data
        static tl::expected<std::shared_ptr<CImageDataResource>, std::string> 
        loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept;

        // Calls loadFromImageFile with flipVertically as true
        static tl::expected<std::shared_ptr<CImageDataResource>, std::string> 
        load(std::filesystem::path location) noexcept;

    private:
        CImageDataResource(tl::optional<std::filesystem::path> location) noexcept;
    };

} // namespace chestnut::engine

