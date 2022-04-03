#include "buffer.hpp"

#include <numeric>


namespace chestnut::engine
{
    CBuffer::CBuffer()
    : m_type(EType::VERTEX), m_usage(EUsage::STATIC_DRAW), m_layout(ELayout::ARRAY_OF_STRUCTS)
    {
        glGenBuffers(1, &m_id);
        m_currentSize = 0;
        m_shouldRebindAttribs = false;
    }

    CBuffer::CBuffer(EType type, EUsage usage, ELayout layout)
    : m_type(type), m_usage(usage), m_layout(layout)
    {
        glGenBuffers(1, &m_id);
        m_currentSize = 0;
        m_shouldRebindAttribs = false;
    }

    CBuffer::~CBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    CBuffer::CBuffer(const CBuffer& other)
    {
        glGenBuffers(1, &m_id);
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;
        m_shouldRebindAttribs = !other.m_vecVertexAttributes.empty(); // because it's a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;
    }

    CBuffer& CBuffer::operator=(const CBuffer& other)
    {
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;
        m_shouldRebindAttribs = !other.m_vecVertexAttributes.empty(); // because it's a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;
        
        return *this;
    }

    CBuffer::CBuffer(CBuffer&& other)
    {
        m_id = other.m_id;
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;
        m_shouldRebindAttribs = other.m_shouldRebindAttribs; // because it's a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;

        other.m_id = 0;
        other.m_currentSize = 0;
        other.m_shouldRebindAttribs = false;
        other.m_vecVertexAttributes.clear();
    }

    CBuffer& CBuffer::operator=(CBuffer&& other)
    {
        m_id = other.m_id;
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;
        m_shouldRebindAttribs = other.m_shouldRebindAttribs; // because it's a different buffer
        m_vecVertexAttributes = other.m_vecVertexAttributes;

        other.m_id = 0;
        other.m_currentSize = 0;
        other.m_shouldRebindAttribs = false;
        other.m_vecVertexAttributes.clear();

        return *this;
    }





    void CBuffer::bind()
    {
        glBindBuffer(m_type, m_id);
    }

    void CBuffer::unbind()
    {
        glBindBuffer(m_type, 0);
    }

    void CBuffer::addAttribute(CVertexAttribute&& attribute)
    {
        m_vecVertexAttributes.push_back(attribute);
        m_shouldRebindAttribs = true;
    }

    bool CBuffer::shouldRebindAttributes() const
    {
        return m_shouldRebindAttribs;
    }

    void CBuffer::rebindAttributes()
    {
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

    void CBuffer::rebindAttributesSOA()
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

    void CBuffer::rebindAttributesAOS()
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

    size_t CBuffer::getUnderlyingDataSize() const
    {
        return std::accumulate(m_vecVertexAttributes.begin(), m_vecVertexAttributes.end(), 0, 
            [](size_t sum, const CVertexAttribute& attribute)
            {
                return sum + attribute.getTypeSize() * attribute.getLength();
            }
        );
    }

    void CBuffer::allocate(size_t size)
    {
        glBufferData(m_type, size, NULL, m_usage);
        m_currentSize = size;

        if(m_layout == ELayout::STRUCT_OF_ARRAYS)
        {
            m_shouldRebindAttribs = true;
        }
    }

    void CBuffer::update(const void* data, size_t size, size_t offset)
    {
        if(offset + size > m_currentSize)
        {
            allocate(size + offset);
        }
        
        glBufferSubData(m_type, offset, size, data);
    }
    
} // namespace chestnut::engine