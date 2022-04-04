#include "buffer.hpp"

namespace chestnut::engine
{
    CBuffer::CBuffer()
    {
        glGenBuffers(1, &m_id);
        m_type = EType::VERTEX;
        m_usage = EUsage::STATIC_DRAW;
        m_layout = ELayout::SINGLE_ARRAY;
        m_currentSize = 0;
    }

    CBuffer::CBuffer(EType type, EUsage usage, ELayout layout)
    : m_type(type), m_usage(usage), m_layout(layout)
    {
        glGenBuffers(1, &m_id);
        m_currentSize = 0;
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
        reserve(other.m_currentSize);
    }

    CBuffer& CBuffer::operator=(const CBuffer& other)
    {
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        reserve(other.m_currentSize);
        
        return *this;
    }

    CBuffer::CBuffer(CBuffer&& other)
    {
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;

        other.m_id = 0;
        other.m_currentSize = 0;
    }

    CBuffer& CBuffer::operator=(CBuffer&& other)
    {
        glDeleteBuffers(1, &m_id);
        
        m_type = other.m_type;
        m_usage = other.m_usage;
        m_layout = other.m_layout;
        m_currentSize = other.m_currentSize;

        other.m_id = 0;
        other.m_currentSize = 0;

        return *this;
    }





    GLuint CBuffer::getID() const
    {
        return m_id;
    }

    CBuffer::EType CBuffer::getType() const
    {
        return m_type;
    }

    CBuffer::EUsage CBuffer::getUsage() const
    {
        return m_usage;
    }

    CBuffer::ELayout CBuffer::getLayout() const
    {
        return m_layout;
    }

    size_t CBuffer::getCurrentSize() const
    {
        return m_currentSize;
    }





    void CBuffer::bind()
    {
        glBindBuffer(m_type, m_id);
    }

    void CBuffer::unbind()
    {
        glBindBuffer(m_type, 0);
    }

    void CBuffer::reserve(size_t size)
    {
        bind();
        glBufferData(m_type, size, NULL, m_usage);
        m_currentSize = size; 
    }

    void CBuffer::update(const void* data, size_t size, size_t offset)
    {
        bind();
        
        if(offset + size > m_currentSize)
        {
            reserve(size + offset);
        }
        
        glBufferSubData(m_type, offset, size, data);
    }
    
} // namespace chestnut::engine
