#ifndef __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__
#define __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__

#include "chestnut/engine/macros.hpp"

#include <GL/glew.h>

#include <string>


namespace chestnut::engine
{
    class CHESTNUT_API CVertexAttribute
    {
    public:
        enum EType
        {
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
        CVertexAttribute();

        template<typename T>
        static CVertexAttribute create(const std::string& name, GLint location, bool isInstanced);


        const std::string& getName() const;
        GLint getLocation() const;
        EType getType() const;
        size_t getTypeSize() const;
        GLint getLength() const;
        GLuint getDivisor() const;

    private:
        CVertexAttribute(const std::string& name, GLint location, EType type, GLint length, bool isInstanced);
    };

} // namespace chestnut::engine


#include "vertex_attribute.inl"


#endif // __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_H__