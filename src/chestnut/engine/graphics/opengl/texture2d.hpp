#ifndef __CHESTNUT_ENGINE_TEXTURE2D_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_H__

#include "../../resources/texture2d_resource.hpp"
#include "../../maths/rectangle.hpp"
#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"

namespace chestnut::engine
{
    class CTexture2D
    {
    protected:
        std::shared_ptr<CTexture2DResource> m_texResource;

    public:
        CTexture2D() = default;
        explicit CTexture2D( std::shared_ptr<CTexture2DResource> resource );

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

#endif // __CHESTNUT_ENGINE_TEXTURE2D_H__