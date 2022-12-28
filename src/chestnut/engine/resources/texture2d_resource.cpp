#include "chestnut/engine/resources/texture2d_resource.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/misc/glu_error_string.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>


namespace chestnut::engine
{
    constexpr GLenum bytesPerPixelToPixelFormat(int bpp)
    {
        switch(bpp)
        {
        case 4:
            return GL_RGBA;
        case 3:
            return GL_RGB;
        case 2:
            return GL_RG;
        case 1:
            return GL_RED;
        default:
            LOG_WARNING( "Invalid bytes per pixel given: " << bpp );
            return 1;
        }
    }




    CTexture2DResource::CTexture2DResource(tl::optional<std::filesystem::path> location) noexcept
    : IResource(location)
    {

    }

    CTexture2DResource::~CTexture2DResource() noexcept
    {
        glDeleteTextures( 1, &m_texID );
    }




    tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
    CTexture2DResource::loadFromImageData(const std::shared_ptr<CImageDataResource>& imageData) noexcept
    {
        if( imageData->m_width != imageData->m_height || ( imageData->m_width & ( imageData->m_width - 1 ) ) != 0 )
        {
            LOG_WARNING("Loading non-power-of-two texture...");
        }

        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        // in case we need to store 1-channel texture
        if(imageData->m_numChannels == 1)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        
        // if data is null it will create a blank texture
        GLenum format = bytesPerPixelToPixelFormat(imageData->m_numChannels);
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            bytesPerPixelToPixelFormat(imageData->m_numChannels), 
            imageData->m_width, 
            imageData->m_height, 
            0, 
            format, 
            GL_UNSIGNED_BYTE, 
            imageData->m_data 
        ); 

        glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
        
        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            const char *msg = (const char *)gluErrorString( err );
            LOG_ERROR( "Error occured while loading texture from pixels! Error: " << msg );
            glDeleteTextures( 1, &texID );
            glBindTexture( GL_TEXTURE_2D, 0 );
            
            return tl::make_unexpected(msg);
        }
        else
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glBindTexture( GL_TEXTURE_2D, 0 );

            std::shared_ptr<CTexture2DResource> resource(new CTexture2DResource(imageData->m_location));
            resource->m_texID = texID;
            resource->m_pixelFormat = format;
            resource->m_width = imageData->m_width;
            resource->m_height = imageData->m_height;

            return resource;
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
    CTexture2DResource::loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept
    {
        auto imageData = CImageDataResource::loadFromPixels(pixelData, width, height, numChannels);
        if(imageData)
        {
            return loadFromImageData(*imageData);
        }
        else
        {
            return tl::make_unexpected(imageData.error());   
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
    CTexture2DResource::loadFromImageFile(std::filesystem::path texturePath) noexcept
    {
        LOG_INFO( "Loading texture from file: " << texturePath << "..." );

        // checks for path existance and extensions are done in CImageDataResource
        auto imageData = CImageDataResource::loadFromImageFile(texturePath, true);
        if(imageData)
        {
            return loadFromImageData(*imageData);
        }
        else
        {
            return tl::make_unexpected(imageData.error());   
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
    CTexture2DResource::loadFromDefinition(std::filesystem::path definitionPath) noexcept
    {
        LOG_INFO( "Loading texture from definition: " << definitionPath << "..." );

        if(!std::filesystem::exists(definitionPath))
        {
            return tl::make_unexpected("File does not exist: " + definitionPath.string());
        }

        auto [ext, supported] = isExtensionSupported(definitionPath, SUPPORTED_FILE_EXTENSIONS_DEFINITIONS);
        if(!supported)
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }


        std::ifstream f(definitionPath);

        if(!f)
        {
            return tl::make_unexpected("Definition file could not be opened");
        }

        try
        {
            auto j = nlohmann::json::parse(f); 
            
            std::filesystem::path imageFilePath;
            std::string filtering;
            j.at("imageFilePath").get_to(imageFilePath);
            j.at("filtering").get_to(filtering);

            if(!imageFilePath.is_absolute())
            {
                imageFilePath = assetPathToAbsolute(imageFilePath);
            }

            auto resource = loadFromImageFile(imageFilePath);
            if(!resource.has_value())
            {
                return resource;
            }

            (**resource).m_location = definitionPath;

            glBindTexture(GL_TEXTURE_2D, resource.value().get()->m_texID);
            if(filtering == "NEAREST")
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                
            }
            else if(filtering == "LINEAR")
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else
            {
                LOG_WARNING("Unsupported texture filtering method: " << filtering);
            }
            glBindTexture(GL_TEXTURE_2D, 0);

            return resource;
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected("Error when parsing the file: " + std::string(e.what()));
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, std::string> 
    CTexture2DResource::load(std::filesystem::path location) noexcept
    {
        if(!std::filesystem::exists(location))
        {
            return tl::make_unexpected("File does not exist: " + location.string());
        }

        auto [ext, isDefinition] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS_DEFINITIONS);
        auto [_, isImageFile] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS_IMAGE_FILES);

        if(isDefinition)
        {
            return loadFromDefinition(location);
        }
        else if(isImageFile)
        {
            return loadFromImageFile(location);
        }
        else
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }
    }

} // namespace chestnut::engine
