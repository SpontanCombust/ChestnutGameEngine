#include "chestnut/engine/resources/texture2d_resource.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/misc/glu_error_string.hpp"

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




    CTexture2DResource::CTexture2DResource() noexcept
    {
        m_texID = 0;
        m_texturePath.reset();
        m_pixelFormat = 0;
        m_width = 0;
        m_height = 0;
    }

    CTexture2DResource::~CTexture2DResource() noexcept
    {
        glDeleteTextures( 1, &m_texID );
    }




    tl::expected<std::shared_ptr<CTexture2DResource>, const char *> CTexture2DResource::loadFromImageData(std::shared_ptr<CImageDataResource> imageData) noexcept
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

            std::shared_ptr<CTexture2DResource> resource = std::make_shared<CTexture2DResource>();
            resource->m_texID = texID;
            resource->m_texturePath = imageData->m_sourcePath;
            resource->m_pixelFormat = format;
            resource->m_width = imageData->m_width;
            resource->m_height = imageData->m_height;

            return resource;
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, const char *> CTexture2DResource::loadFromPixels(const unsigned char *pixelData, int width, int height, int numChannels) noexcept
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

    tl::expected<std::shared_ptr<CTexture2DResource>, const char *> CTexture2DResource::loadFromFile(const char *texturePath) noexcept
    {
        LOG_INFO( "Loading texture from file: " << texturePath << "..." );

        auto imageData = CImageDataResource::loadFromFile(texturePath, true);
        if(imageData)
        {
            return loadFromImageData(*imageData);
        }
        else
        {
            return tl::make_unexpected(imageData.error());   
        }
    }

} // namespace chestnut::engine

