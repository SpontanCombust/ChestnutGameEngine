#include "chestnut/engine/graphics/opengl/vertex_attribute.hpp"

namespace chestnut::engine
{
    CVertexAttribute::CVertexAttribute()
    : m_name(""), m_location(-1), m_type(EType::FLOAT), m_length(0), m_divisor(0)
    {

    }

    CVertexAttribute::CVertexAttribute(const std::string& name, GLint location, EType type, GLint length, bool isInstanced)
    : m_name(name), m_location(location), m_type(type), m_length(length)
    {
        if(isInstanced)
        {
            m_divisor = 1;
        }
        else
        {
            m_divisor = 0;
        }
    }

    const std::string& CVertexAttribute::getName() const
    {
        return m_name;
    }

    GLint CVertexAttribute::getLocation() const
    {
        return m_location;
    }

    GLint CVertexAttribute::getLength() const
    {
        return m_length;
    }

    CVertexAttribute::EType CVertexAttribute::getType() const
    {
        return m_type;
    }

    size_t CVertexAttribute::getTypeSize() const
    {
        switch(m_type)
        {
        case EType::INT:
        case EType::UINT:
        case EType::FLOAT:
            return 4;
        default:
            return 0;
        }
    }

    GLuint CVertexAttribute::getDivisor() const
    {
        return m_divisor;
    }

} // namespace chestnut::engine
