#pragma once


#include "chestnut/engine/macros.hpp"
#include "../../resources/texture2d_resource.hpp"
#include "../../maths/rectangle.hpp"
#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"

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

