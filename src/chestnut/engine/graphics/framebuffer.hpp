#ifndef __CHESTNUT_ENGINE_FRAMEBUFFER_H__
#define __CHESTNUT_ENGINE_FRAMEBUFFER_H__

#include "texture2d.hpp"

namespace chestnut::engine
{
    class CFramebuffer
    {
    private:
        GLuint m_fbo;
        GLuint m_rbo;

    public:
        CFramebuffer();
        CFramebuffer( const CFramebuffer& other ) = delete; // force using pointer/reference to pass the buffer
        CFramebuffer( CFramebuffer&& other );
        // Can throw exception on error
        CFramebuffer( const CTexture2D& target );

        ~CFramebuffer();


        GLuint getID() const;


        void bind() const;

        void unbind() const;


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