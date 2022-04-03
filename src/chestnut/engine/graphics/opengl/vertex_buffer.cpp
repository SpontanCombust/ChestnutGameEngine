#include "vertex_buffer.hpp"

#include <numeric>


namespace chestnut::engine
{    
    CVertexBuffer::CVertexBuffer()
    : IBuffer()
    {
        m_layout = ELayout::STRUCT_OF_ARRAYS;
        m_shouldRebindAttribs = false;
    }

    CVertexBuffer::CVertexBuffer(EUsage usage, ELayout layout)
    : IBuffer(usage), m_layout(layout)
    {
        m_shouldRebindAttribs = false;   
    }

    CVertexBuffer::CVertexBuffer(const CVertexBuffer& other)
    : IBuffer(other)
    {
        m_layout = other.m_layout;
        m_shouldRebindAttribs = !other.m_vecVertexAttributes.empty(); // because this is a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;
    }

    CVertexBuffer& CVertexBuffer::operator=(const CVertexBuffer& other)
    {
        IBuffer::operator=(other);
        m_layout = other.m_layout;
        m_shouldRebindAttribs = !other.m_vecVertexAttributes.empty(); // because this is a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;

        return *this;
    }

    CVertexBuffer::CVertexBuffer(CVertexBuffer&& other)
    : IBuffer(std::move(other))
    {
        m_layout = other.m_layout;
        m_shouldRebindAttribs = other.m_shouldRebindAttribs;
        m_vecVertexAttributes = std::move(other.m_vecVertexAttributes);
    }

    CVertexBuffer& CVertexBuffer::operator=(CVertexBuffer&& other)
    {
        IBuffer::operator=(std::move(other));
        m_layout = other.m_layout;
        m_shouldRebindAttribs = other.m_shouldRebindAttribs;
        m_vecVertexAttributes = std::move(other.m_vecVertexAttributes);

        return *this;
    }




    void CVertexBuffer::addAttribute(const CVertexAttribute& attribute)
    {
        m_vecVertexAttributes.push_back(attribute);
        m_shouldRebindAttribs = true;
    }

    bool CVertexBuffer::shouldRebindAttributes() const
    {
        return m_shouldRebindAttribs;
    }

    void CVertexBuffer::rebindAttributes()
    {
        bind();
        
        if (m_layout == ELayout::STRUCT_OF_ARRAYS)
        {
            rebindAttributesSOA();
        }
        else
        {
            rebindAttributesAOS();
        }

        m_shouldRebindAttribs = false;
    }

    void CVertexBuffer::rebindAttributesSOA()
    {
        size_t arraySize = m_currentSize / getUnderlyingDataSize();

        size_t attribOffset = 0;
        for(const auto& attribute : m_vecVertexAttributes)
        {
            glEnableVertexAttribArray(attribute.getLocation());
            if(attribute.getType() == CVertexAttribute::EType::FLOAT)
            {
                glVertexAttribPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    GL_FALSE,
                    0,
                    (const void *)attribOffset
                );
            }
            else
            {
                glVertexAttribIPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    0,
                    (const void *)attribOffset
                );  
            }
            glVertexAttribDivisor(attribute.getLocation(), attribute.getDivisor());

            attribOffset += arraySize * attribute.getTypeSize() * attribute.getLength();
        }
    }

    void CVertexBuffer::rebindAttributesAOS()
    {
        const size_t structSize = getUnderlyingDataSize();

        size_t attribOffset = 0;
        for(const auto& attribute : m_vecVertexAttributes)
        {
            glEnableVertexAttribArray(attribute.getLocation());
            if(attribute.getType() == CVertexAttribute::EType::FLOAT)
            {
                glVertexAttribPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    GL_FALSE,
                    structSize,
                    (const void *)attribOffset
                );
            }
            else
            {
                glVertexAttribIPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    structSize,
                    (const void *)attribOffset
                );   
            }
            glVertexAttribDivisor(attribute.getLocation(), attribute.getDivisor());

            attribOffset += attribute.getTypeSize() * attribute.getLength();
        }
    }

    size_t CVertexBuffer::getUnderlyingDataSize() const
    {
        return std::accumulate(m_vecVertexAttributes.begin(), m_vecVertexAttributes.end(), 0, 
            [](size_t sum, const CVertexAttribute& attribute)
            {
                return sum + attribute.getTypeSize() * attribute.getLength();
            }
        );
    }





    GLenum CVertexBuffer::getTypeEnum() const 
    {
        return GL_ARRAY_BUFFER;
    }

    void CVertexBuffer::reserve(size_t size)
    {
        IBuffer::reserve(size);

        if(m_layout == ELayout::STRUCT_OF_ARRAYS)
        {
            m_shouldRebindAttribs = true;
        }
    }


} // namespace chestnut::engine
