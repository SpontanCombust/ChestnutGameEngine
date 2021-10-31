#include "framebuffer.hpp"

#include "../debug/log.hpp"

namespace chestnut::engine
{
    CFramebuffer::CFramebuffer( int width, int height ) 
    {
        m_fbo = 0;
        m_rbo = 0;
        m_width = width;
        m_height = height;
        m_clearColor = { 0.f, 0.f, 0.f, 1.f };
    }

    CFramebuffer::CFramebuffer( const CTexture2D& target ) 
    {
        m_fbo = 0;
        m_rbo = 0;
        m_clearColor = { 0.f, 0.f, 0.f, 1.f };
        setTarget( target );
    }

    CFramebuffer::CFramebuffer( CFramebuffer&& other ) 
    {
        m_fbo = other.m_fbo;
        m_rbo = other.m_rbo;
        m_width = other.m_width;
        m_height = other.m_height;
        m_clearColor = other.m_clearColor;

        other.m_fbo = 0;
        other.m_rbo = 0;
    }

    CFramebuffer& CFramebuffer::operator=( CFramebuffer&& other ) 
    {
        m_fbo = other.m_fbo;
        m_rbo = other.m_rbo;
        m_width = other.m_width;
        m_height = other.m_height;
        m_clearColor = other.m_clearColor;

        other.m_fbo = 0;
        other.m_rbo = 0;

        return *this;
    }

    CFramebuffer::~CFramebuffer() 
    {
        destroyBufferIfSetToTexture();
    }

    GLuint CFramebuffer::getID() const
    {
        return m_fbo;
    }

    int CFramebuffer::getWidth() const
    {
        return m_width;
    }

    int CFramebuffer::getHeight() const
    {
        return m_height;
    }

    vec4f CFramebuffer::getClearColor() const
    {
        return m_clearColor;
    }

    void CFramebuffer::setClearColor( const vec4f& color ) 
    {
        m_clearColor = color;
    }

    void CFramebuffer::bind() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
        glViewport( 0, 0, m_width, m_height );
        glClearColor( m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w );
    }

    void CFramebuffer::unbind() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }

    void CFramebuffer::clear() 
    {
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void CFramebuffer::setTarget( const CTexture2D& target ) 
    {
        destroyBufferIfSetToTexture();



        GLuint rbo;

        glGenRenderbuffers( 1, &rbo );
        glBindRenderbuffer( GL_RENDERBUFFER, rbo );
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, target.getWidth(), target.getHeight() );

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while setting a target. Error: " << gluErrorString( err ) );
            glBindRenderbuffer( GL_RENDERBUFFER, 0 );
            glDeleteRenderbuffers( 1, &rbo );

            throw ChestnutException( "Failed to create OpenGL renderbuffer for the framebuffer!" );
        }

        glBindRenderbuffer( GL_RENDERBUFFER, 0 );



        GLuint fbo;

        glGenFramebuffers( 1, &fbo );
        glBindFramebuffer( GL_FRAMEBUFFER, fbo );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target.getID(), 0 );
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo );

        if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
        {
            LOG_ERROR( "Error occured while setting a target. Error: " << "Framebuffer is not complete" );
            glDeleteRenderbuffers( 1, &rbo );
            glDeleteFramebuffers( 1, &fbo );

            throw ChestnutException( "Failed to complete OpenGL framebuffer!" );
        }

        glBindRenderbuffer( GL_RENDERBUFFER, 0 );


        m_fbo = fbo;
        m_rbo = rbo;
        m_width = target.getWidth();        
        m_height = target.getHeight();
    }

    void CFramebuffer::resetTarget() 
    {
        destroyBufferIfSetToTexture();
    }

    bool CFramebuffer::hasTarget() const
    {
        return m_fbo != 0;
    }

    void CFramebuffer::destroyBufferIfSetToTexture() 
    {
        if( m_fbo != 0 )
        {
            glDeleteFramebuffers( 1, &m_fbo );
            glDeleteRenderbuffers( 1, &m_rbo );

            m_fbo = 0;
            m_rbo = 0;
        }
    }

} // namespace chestnut::engine
