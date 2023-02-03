#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/image_data_resource.hpp"

#include <glad/glad.h>
#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include <string>


namespace chestnut::engine
{
    // A texture resource class that provides automatic texture deallocation on object deletion
    class CHESTNUT_API CTexture2DResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_IMAGE_FILES {
            "jpg", "jpeg", "png", "tga", "bmp", "gif"
        };
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_DEFINITIONS = {
            "texture", "tex"
        };
        
        GLuint m_texID = 0;
        GLenum m_pixelFormat = 0;
        int m_width = 0, m_height = 0;

    public: 
        ~CTexture2DResource() noexcept;

        static tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
        loadFromImageData(const std::shared_ptr<CImageDataResource>& imageData) noexcept;

        // pixelData can be null if you want to only create a blank texture
        static tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
        loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept;

        static tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
        loadFromImageFile(std::filesystem::path texturePath) noexcept;

        static tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
        loadFromDefinition(std::filesystem::path definitionPath) noexcept;

        // Calls either loadFromImageFile or loadFromDefinition, depending on target file type
        static tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
        load(std::filesystem::path location) noexcept;

    private:
        CTexture2DResource(tl::optional<std::filesystem::path> location) noexcept;
    };



} // namespace chestnut::engine

