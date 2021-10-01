#include "texture2d_resource.hpp"

#include "../debug/log.hpp"
#include "../misc/exception.hpp"

#include <SDL2/SDL_image.h>

namespace chestnut::engine
{
    GLuint loadOpenGLTexture2DFromPixels( void *pixels, int width, int height, GLenum pixelFormat )
    {
        GLuint texID;

        glGenTextures( 1, &texID );

        glBindTexture( GL_TEXTURE_2D, texID );
        
        glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, pixels );

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while loading texture from pixels! Error:" );
            LOG_ERROR( gluErrorString( err ) );
            glDeleteTextures( 1, &texID );
            glBindTexture( GL_TEXTURE_2D, 0 );
            
            throw ChestnutException( "Failed to send the texture data to the GPU!" );
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

    GLuint loadOpenGLTexture2DFromFile( const std::string& path, int& width, int& height, GLenum& pixelFormat )
    {
        SDL_Surface *surf = IMG_Load( path.c_str() );

        if( !surf )
        {
            throw ChestnutException( "Failed to load texture from file: " + path );
        }

        if( surf->w != surf->h || ( surf->w & ( surf->w - 1 ) ) != 0 )
        {
            LOG_WARNING( "Loading non-power-of-two texture from " << path );
        }

        width = surf->w;
        height = surf->h;
        void *pixels = surf->pixels;

        int bytesPerPixel = (int)surf->format->BytesPerPixel;
        bool firstRed = ( surf->format->Rmask == 0x000000ff );

        if( bytesPerPixel == 4 )
        {
            if( firstRed )
            {
                pixelFormat = GL_RGBA;
            }
            else
            {
                pixelFormat = GL_BGRA;
            }
        }
        else if( bytesPerPixel == 3 )
        {
            if( firstRed )
            {
                pixelFormat = GL_RGB;
            }
            else
            {
                pixelFormat = GL_BGR;
            }
        }
        else if( bytesPerPixel == 2 )
        {
            pixelFormat = GL_RG;
        }
        else
        {
            pixelFormat = GL_RED;
        }
        
        GLuint texID;
        bool loaded;
        std::string msg;

        try
        {
            texID = loadOpenGLTexture2DFromPixels( pixels, width, height, pixelFormat );
            loaded = true;
        }
        catch( const std::exception& e )
        {
            msg = e.what();
            loaded = false;
        }

        SDL_FreeSurface( surf );

        if( loaded )
        {
            return texID;
        }
        else
        {
            throw ChestnutException( msg );
        }
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

    bool CTexture2DResource::isValid() const
    {
        if( m_texID != 0 )
        {
            return true;
        }
        return false;
    }

    CTexture2DResource::~CTexture2DResource() 
    {
        if( isValid() )
        {
            glDeleteTextures( 1, &m_texID );
        }
    }




    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromPixels( void *pixels, int width, int height, GLenum pixelFormat )
    {
        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTexture2DFromPixels( pixels, width, height, pixelFormat );

        CTexture2DResource *resource = new CTexture2DResource();
        resource->m_texID = texID;
        resource->m_texturePath = "";
        resource->m_wasLoadedFromFile = false;
        resource->m_pixelFormat = pixelFormat;
        resource->m_width = width;
        resource->m_height = height;

        return std::shared_ptr<CTexture2DResource>( resource );
    }

    std::shared_ptr< CTexture2DResource > loadTexture2DResourceFromFile( const std::string& texturePath )
    {
        int width, height;
        GLenum pixelFormat;

        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTexture2DFromFile( texturePath, width, height, pixelFormat );

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

