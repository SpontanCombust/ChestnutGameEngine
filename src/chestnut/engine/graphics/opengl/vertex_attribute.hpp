#ifndef __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__
#define __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__

#include <GL/glew.h>
#include <tl/optional.hpp>

#include <string>

namespace chestnut::engine
{
    class CVertexAttribute
    {
    public:
        enum EType
        {
            BYTE    = GL_BYTE,
            UBYTE   = GL_UNSIGNED_BYTE,
            SHORT   = GL_SHORT,
            USHORT  = GL_UNSIGNED_SHORT,
            INT     = GL_INT,
            UINT    = GL_UNSIGNED_INT,
            FLOAT   = GL_FLOAT
        };

    private:
        std::string m_name;
        GLint m_location;
        EType m_type;
        GLint m_length;
        GLuint m_divisor;

    public:
        CVertexAttribute(std::string name, GLint location, EType type, GLint length, bool isInstanced);

        const std::string& getName() const;
        GLint getLocation() const;
        EType getType() const;
        size_t getTypeSize() const;
        GLint getLength() const;
        GLuint getDivisor() const;

        template<typename T>
        static tl::optional<EType> deduceTypeEnum();
    };

} // namespace chestnut::engine


#include "vertex_attribute.inl"


#endif // __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__