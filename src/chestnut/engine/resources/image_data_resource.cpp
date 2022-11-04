#include "chestnut/engine/resources/image_data_resource.hpp"

#include "chestnut/engine/debug/log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

#include <cstring>


namespace chestnut::engine
{    
    CImageDataResource::CImageDataResource() noexcept
    : m_sourcePath(tl::nullopt),
      m_data(nullptr),
      m_width(0),
      m_height(0),
      m_numChannels(0)
    {

    }

    CImageDataResource::~CImageDataResource() noexcept
    {
        if(m_data)
        {
            // if was loaded from file
            if(m_sourcePath.has_value())
            {
                stbi_image_free(m_data);
            }
            else
            {
                delete[] m_data;   
            }
        }
    }



    tl::expected<std::shared_ptr<CImageDataResource>, const char *> CImageDataResource::loadFromFile(const char *imagePath, bool flipVertically) noexcept
    {
        LOG_INFO( "Loading image from file: " << imagePath << "..." );

        stbi_set_flip_vertically_on_load(flipVertically);

        int w, h, ch;
        unsigned char *data = stbi_load(imagePath, &w, &h, &ch, 0); 
        if(data)
        {
            CImageDataResource *resource = new CImageDataResource();
            resource->m_sourcePath = imagePath;
            resource->m_data = data;
            resource->m_width = w;
            resource->m_height = h;
            resource->m_numChannels = ch;

            return std::shared_ptr<CImageDataResource>(resource);
        }
        else
        {
            return tl::make_unexpected(stbi_failure_reason());
        }
    }

    tl::expected<std::shared_ptr<CImageDataResource>, const char *> CImageDataResource::loadFromPixels(const unsigned char *data, int width, int height, int numChannels) noexcept
    {
        if(width <= 0 || height <= 0)
        {
            return tl::make_unexpected("Width and height must be greater than 0");
        }
        else if(numChannels <= 0 || numChannels > 4)
        {
            return tl::make_unexpected("Number of channels must be between 1 and 4");
        }

        CImageDataResource *resource = new CImageDataResource();
        resource->m_sourcePath = std::move(tl::nullopt);
        resource->m_data = new unsigned char[width * height * numChannels];
        if(data) {
            std::memcpy(resource->m_data, data, width * height * numChannels);
        } else {
            std::memset(resource->m_data, 0, width * height * numChannels);
        }
        resource->m_width = width;
        resource->m_height = height;
        resource->m_numChannels = numChannels;

        return std::shared_ptr<CImageDataResource>(resource);
    }

} // namespace chestnut::engine
