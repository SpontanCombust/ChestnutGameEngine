#include "dynamic_texture2d_resource.hpp"

#include "../debug/log.hpp"
#include "../misc/exception.hpp"

namespace chestnut::engine
{
    std::shared_ptr< CDynamicTexture2DResource > createDynamicTexture2DResource( int width, int height, GLenum pixelFormat )
    {
        GLuint texID;

        glGenTextures( 1, &texID );
        glBindTexture( GL_TEXTURE_2D, texID );
        glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, NULL );

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while creating a dynamic texture. Error: " << gluErrorString( err ) );
            glDeleteTextures( 1, &texID );
            glBindTexture( GL_TEXTURE_2D, 0 );

            throw ChestnutException( "Failed to create OpenGL color buffer for the dynamic texture!" );
        }

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glBindTexture( GL_TEXTURE_2D, 0 );



        GLuint rbo;

        glGenRenderbuffers( 1, &rbo );
        glBindRenderbuffer( GL_RENDERBUFFER, rbo );
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height );

        err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while creating a dynamic texture. Error: " << gluErrorString( err ) );
            glBindRenderbuffer( GL_RENDERBUFFER, 0 );
            glDeleteTextures( 1, &texID );
            glDeleteRenderbuffers( 1, &rbo );

            throw ChestnutException( "Failed to create OpenGL renderbuffer for the dynamic texture!" );
        }

        glBindRenderbuffer( GL_RENDERBUFFER, 0 );



        GLuint fbo;

        glGenFramebuffers( 1, &fbo );
        glBindFramebuffer( GL_FRAMEBUFFER, fbo );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0 );
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo );

        if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
        {
            LOG_ERROR( "Error occured while creating a dynamic texture. Error: " << "Framebuffer is not complete" );
            glBindRenderbuffer( GL_RENDERBUFFER, 0 );
            glDeleteTextures( 1, &texID );
            glDeleteRenderbuffers( 1, &rbo );
            glDeleteFramebuffers( 1, &fbo );

            throw ChestnutException( "Failed to complete OpenGL framebuffer for the dynamic texture!" );
        }

        glBindRenderbuffer( GL_RENDERBUFFER, 0 );



        CDynamicTexture2DResource *dynamicTexture = new CDynamicTexture2DResource();
        dynamicTexture->m_texID = texID;
        dynamicTexture->m_width = width;
        dynamicTexture->m_height = height;
        dynamicTexture->m_pixelFormat = pixelFormat;
        dynamicTexture->m_rbo = rbo;
        dynamicTexture->m_fbo = fbo;

        return std::shared_ptr< CDynamicTexture2DResource >( dynamicTexture );
    }





    CDynamicTexture2DResource::CDynamicTexture2DResource() 
    {
        m_rbo = 0;
        m_fbo = 0;
    }

    CDynamicTexture2DResource::~CDynamicTexture2DResource() 
    {
        if( isValid() )
        {
            glDeleteRenderbuffers( 1, &m_rbo );
            glDeleteFramebuffers( 1, &m_fbo );
        }
    }

    bool CDynamicTexture2DResource::isValid() const 
    {
        if( m_texID != 0 && m_rbo != 0 && m_fbo != 0 )
        {
            return true;
        }

        return false;
    }

} // namespace chestnut::engine
