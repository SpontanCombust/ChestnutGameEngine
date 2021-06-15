#include "texture2d_resource.hpp"

#include "engine/debug/debug.hpp"
#include "engine/misc/exception.hpp"

namespace chestnut
{
    GLuint loadOpenGLTextureFromPixels( void *pixels, int width, int height, GLenum pixelFormat )
    {
        GLuint texID;

        glGenTextures( 1, &texID );

        glBindTexture( GL_TEXTURE_2D, texID );
        
        glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, pixels );

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "TEXTURE2D_RESOURCE", "Error occured while loading texture from pixels! Error:" );
            LOG_CHANNEL( "TEXTURE2D_RESOURCE", (char *)gluErrorString( err ) );
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

    GLuint loadOpenGLTextureFromFile( const std::string& path, int& width, int& height, GLenum& pixelFormat )
    {
        SDL_Surface *surf = IMG_Load( path.c_str() );

        if( !surf )
        {
            throw ChestnutException( "Failed to load texture from file: " + path );
        }

        if( surf->w != surf->h || ( surf->w & ( surf->w - 1 ) ) != 0 )
        {
            LOG_CHANNEL( "TEXTURE2D_RESOURCE", "Warning! Loading non-power-of-two texture from " << path );
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
            texID = loadOpenGLTextureFromPixels( pixels, width, height, pixelFormat );
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
        this->texID = 0;
        this->pixelFormat = 0;
        this->width = 0;
        this->height = 0;
    }

    CTexture2DResource::CTexture2DResource( GLuint texID, GLenum pixelFormat, int width, int height ) 
    {
        this->texID = texID;
        this->pixelFormat = pixelFormat;
        this->width = width;
        this->height = height;
    }

    bool CTexture2DResource::isValid() const
    {
        if( texID != 0 )
        {
            return true;
        }
        return false;
    }

    CTexture2DResource::~CTexture2DResource() 
    {
        if( isValid() )
        {
            glDeleteTextures( 1, &texID );
        }
    }




    std::shared_ptr< CTexture2DResource > loadTextureResourceFromPixels( void *pixels, int width, int height, unsigned int pixelFormat )
    {
        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTextureFromPixels( pixels, width, height, pixelFormat );

        return std::make_shared< CTexture2DResource >( texID, pixelFormat, width, height );
    }

    std::shared_ptr< CTexture2DResource > loadTextureResourceFromFile( const std::string& path )
    {
        int width, height;
        GLenum pixelFormat;

        // let the exception propagate if it happens
        GLuint texID = loadOpenGLTextureFromFile( path, width, height, pixelFormat );

        return std::make_shared< CTexture2DResource >( texID, pixelFormat, width, height );        
    }

} // namespace chestnut

