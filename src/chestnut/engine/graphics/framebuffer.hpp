#ifndef __CHESTNUT_ENGINE_FRAMEBUFFER_H__
#define __CHESTNUT_ENGINE_FRAMEBUFFER_H__

#include "texture2d.hpp"
#include "../maths/vector4.hpp"

namespace chestnut::engine
{
    class CFramebuffer
    {
    private:
        GLuint m_fbo;
        GLuint m_rbo;
        int m_width, m_height;
        vec4f m_clearColor;

    public:
        CFramebuffer( int width, int height );
        CFramebuffer( const CFramebuffer& other ) = delete;
        CFramebuffer( CFramebuffer&& other );
        CFramebuffer& operator=( CFramebuffer&& other );
        // Can throw exception on error
        CFramebuffer( const CTexture2D& target );

        ~CFramebuffer();


        GLuint getID() const;

        int getWidth() const;
        int getHeight() const;

        vec4f getClearColor() const;
        void setClearColor( const vec4f& color );


        void bind() const;
        void unbind() const;
        
        void clear();


        // Can throw exception on error
        void setTarget( const CTexture2D& target );
        // The target will be the default OpenGL window buffer
        void resetTarget();

        // If not then the target is directly OpenGL window buffer
        bool hasTarget() const;

    private:
        void destroyBufferIfSetToTexture();  
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_FRAMEBUFFER_H__