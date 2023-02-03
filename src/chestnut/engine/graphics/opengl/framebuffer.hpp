#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/opengl/texture2d.hpp"
#include "chestnut/engine/maths/vector4.hpp"

#include <tl/optional.hpp>


namespace chestnut::engine
{
    class CHESTNUT_API CFramebuffer
    {
    private:
        GLuint m_fbo;
        GLuint m_rbo;
        int m_width, m_height;
        vec4f m_clearColor;

        CTexture2D m_target;


    public:
        CFramebuffer( int width, int height );
        CFramebuffer( const CFramebuffer& other ) = delete;
        CFramebuffer( CFramebuffer&& other );
        CFramebuffer& operator=( CFramebuffer&& other );
        // Will set to default framebuffer if target is invalid or error occurs
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


        // Won't change the target if given target is invalid or error occurs
        void setTarget( const CTexture2D& target );
        // The target will be the default OpenGL window buffer
        void resetTarget();
        // If not then the target is directly OpenGL window buffer
        bool hasTarget() const;
        // If returns None then the target is directly OpenGL window buffer
        tl::optional<CTexture2D> getTarget() const;


    private:
        void destroyBufferIfSetToTexture();  
    };

} // namespace chestnut::engine

