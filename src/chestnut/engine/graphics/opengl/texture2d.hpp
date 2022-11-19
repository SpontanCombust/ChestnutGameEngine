#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/texture2d_resource.hpp"
#include "chestnut/engine/maths/rectangle.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CTexture2D
    {
    protected:
        std::shared_ptr<CTexture2DResource> m_texResource;

    public:
        CTexture2D() = default;
        explicit CTexture2D( std::shared_ptr<CTexture2DResource> resource );
        explicit CTexture2D( const std::shared_ptr<CImageDataResource>& resource );

        virtual void setResource(const std::shared_ptr<CTexture2DResource>& resource);
        const std::shared_ptr<CTexture2DResource>& getResource() const;
        bool isValid() const;

        GLuint getID() const;

        void bind() const;
        void unbind() const;

        GLenum getPixelFormat() const;
        int getWidth() const;
        int getHeight() const;
        vec2i getSize() const;

        void setFiltering( GLint minifyingFilter, GLint magnifyingFilter );
        void setWrapping( GLint wrapS, GLint wrapT );
    };   

} // namespace chestnut::engine

