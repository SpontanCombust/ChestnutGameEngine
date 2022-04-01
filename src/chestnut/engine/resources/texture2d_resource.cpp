#include "texture2d_resource.hpp"

#include "../debug/log.hpp"
#include "../misc/exception.hpp"

#include <SDL2/SDL_image.h>

#include <cstring>

namespace chestnut::engine
{
    int pixelFormatToBytesPerPixel( GLenum format )
    {
        switch( format )
        {
        case GL_RGBA:
        case GL_BGRA:
            return 4;
        case GL_RGB:
        case GL_BGR:
            return 3;
        case GL_RG:
            return 2;
        case GL_RED:
            return 1;
        default:
            LOG_WARNING( "Unknown pixel format given: " << format );
            return 1;
        }
    }

    GLenum bytesPerPixelToPixelFormat( int bpp, bool redFirst )
    {
        switch( bpp )
        {
        case 4:
            return redFirst ? GL_RGBA : GL_BGRA;
        case 3:
            return redFirst ? GL_RGB : GL_BGR;
        case 2:
            return GL_RG;
        case 1:
            return GL_RED;
        default:
            LOG_WARNING( "Invalid bytes per pixel given: " << bpp );
            return 1;
        }
    }

    // When we send texture data to OpenGL it samples texture coordinates in row order opposite to how they are loaded from system
    // We usually expect the (0,0) point to the upper left corner of the image, whereas OpenGL expects it to be the LOWER left corner
    // So if we send them as-is, the rendered image is flipped upside down
    // To mitigate this without 'hacking' the UV coordinates inside the renderer (that could break things down the road) 
    // we're just gonna flip the image before we send it  
    std::unique_ptr<unsigned char> getPixelsFlippedVertically( const void *pixels, int width, int height, int bytesPerPixel )
    {
        const unsigned char *pixels8 = (const unsigned char *)pixels;
        unsigned char *flipped8 = new unsigned char[ width * height * bytesPerPixel ];

        for (int i = 0; i < height; i++)
        {
            // copy pixel rows in opposite order to how they are in "pixels"
            // basically flip the image upside down
            std::memcpy( flipped8 + ( height - 1 - i ) * ( width * bytesPerPixel ), 
                         pixels8  + i * width * bytesPerPixel, 
                         width * bytesPerPixel );
        }

        return std::unique_ptr<unsigned char>(flipped8);
    }



    GLuint loadOpenGLTexture2DFromPixels( const void *pixels, int width, int height, GLenum pixelFormat, bool flipPixelsVertically )
    {
        GLuint texID;
        glGenTextures( 1, &texID );
        glBindTexture( GL_TEXTURE_2D, texID );


        int bpp = pixelFormatToBytesPerPixel( pixelFormat );

        // in case we need to store 1-channel texture
        if( bpp == 1 )
        {
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        }
        else
        {
            glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
        }
        
        
        if( pixels )
        {
            if( flipPixelsVertically )
            {
                auto flipped = getPixelsFlippedVertically( pixels, width, height, bpp );
                glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, flipped.get() );
            }
            else
            {
                glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, pixels ); 
            }
        }
        else
        {
            glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, NULL );
        }
        

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            const char *msg = (const char *)gluErrorString( err );
            LOG_ERROR( "Error occured while loading texture from pixels! Error: " << msg );
            glDeleteTextures( 1, &texID );
            glBindTexture( GL_TEXTURE_2D, 0 );
            
            throw ChestnutResourceLoadException( "CTexture2DResource", "[loaded directly from pixel data]", (char *)msg );
        }
        else
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

            glBindTexture( GL_TEXTURE_2D, 0 );

            return texID;
        }
    }

    GLuint loadOpenGLTexture2DFromFile( const char *path, int *width, int *height, GLenum *pixelFormat )
    {
        SDL_Surface *surf = IMG_Load( path );

        if( !surf )
        {
            throw ChestnutResourceLoadException( "CTexture2DResource", path, "failed to load image file" );
        }

        if( surf->w != surf->h || ( surf->w & ( surf->w - 1 ) ) != 0 )
        {
            LOG_WARNING( "Loading non-power-of-two texture from " << path );
        }

        *width = surf->w;
        *height = surf->h;
        void *pixels = surf->pixels;

        int bytesPerPixel = (int)surf->format->BytesPerPixel;
        bool firstRed = ( surf->format->Rmask == 0x000000ff );

        *pixelFormat = bytesPerPixelToPixelFormat( bytesPerPixel, firstRed );
        
        GLuint texID;

        try
        {
            texID = loadOpenGLTexture2DFromPixels( pixels, *width, *height, *pixelFormat, true );  
        }
        catch( const ChestnutResourceLoadException& e )
        {
            SDL_FreeSurface( surf );
            throw ChestnutResourceLoadException( "CTexture2DResource", path, e.reason );
        }

        SDL_FreeSurface( surf );
        return texID;
    }




    CTexture2DResource::CTexture2DResource() 
    {
        m_texID = 0;
        m_texturePath = "";
        m_wasLoadedFromFile = false;
        m_pixelFormat = 0;
        m_width = 0;
        m_height = 0;
    }

    CTexture2DResource::~CTexture2DResource() 
    {
        glDeleteTextures( 1, &m_texID );
    }




    std::shared_ptr<CTexture2DResource> CTexture2DResource::loadFromPixels( const void *pixels, int width, int height, GLenum pixelFormat, bool flipPixelsVertically )
    {
        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTexture2DFromPixels( pixels, width, height, pixelFormat, flipPixelsVertically );

        CTexture2DResource *resource = new CTexture2DResource();
        resource->m_texID = texID;
        resource->m_texturePath = "";
        resource->m_wasLoadedFromFile = false;
        resource->m_pixelFormat = pixelFormat;
        resource->m_width = width;
        resource->m_height = height;

        return std::shared_ptr<CTexture2DResource>( resource );
    }

    std::shared_ptr<CTexture2DResource> CTexture2DResource::loadFromFile( const char *texturePath )
    {
        int width, height;
        GLenum pixelFormat;

        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTexture2DFromFile( texturePath, &width, &height, &pixelFormat );

        CTexture2DResource *resource = new CTexture2DResource();
        resource->m_texID = texID;
        resource->m_texturePath = texturePath;
        resource->m_wasLoadedFromFile = true;
        resource->m_pixelFormat = pixelFormat;
        resource->m_width = width;
        resource->m_height = height;

        return std::shared_ptr<CTexture2DResource>( resource );
    }

} // namespace chestnut::engine

