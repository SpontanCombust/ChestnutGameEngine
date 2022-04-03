#include "buffer.hpp"

namespace chestnut::engine
{
    IBuffer::IBuffer()
    {
        glGenBuffers(1, &m_id);
        m_usage = EUsage::STATIC_DRAW;
        m_currentSize = 0;
    }

    IBuffer::IBuffer(EUsage usage)
    : m_usage(usage)
    {
        glGenBuffers(1, &m_id);
        m_currentSize = 0;
    }

    IBuffer::~IBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    IBuffer::IBuffer(const IBuffer& other)
    {
        glGenBuffers(1, &m_id);
        m_usage = other.m_usage;
        reserve(other.m_currentSize);
    }

    IBuffer& IBuffer::operator=(const IBuffer& other)
    {
        m_usage = other.m_usage;
        reserve(other.m_currentSize);
        
        return *this;
    }

    IBuffer::IBuffer(IBuffer&& other)
    {
        m_id = other.m_id;
        m_usage = other.m_usage;
        m_currentSize = other.m_currentSize;

        other.m_id = 0;
        other.m_currentSize = 0;
    }

    IBuffer& IBuffer::operator=(IBuffer&& other)
    {
        glDeleteBuffers(1, &m_id);
        
        m_id = other.m_id;
        m_usage = other.m_usage;
        m_currentSize = other.m_currentSize;

        other.m_id = 0;
        other.m_currentSize = 0;

        return *this;
    }





    void IBuffer::bind()
    {
        glBindBuffer(getTypeEnum(), m_id);
    }

    void IBuffer::unbind()
    {
        glBindBuffer(getTypeEnum(), 0);
    }

    void IBuffer::reserve(size_t size)
    {
        bind();
        glBufferData(getTypeEnum(), size, NULL, m_usage);
        m_currentSize = size; 
    }

    void IBuffer::update(const void* data, size_t size, size_t offset)
    {
        bind();
        
        if(offset + size > m_currentSize)
        {
            reserve(size + offset);
        }
        
        glBufferSubData(getTypeEnum(), offset, size, data);
    }
    
} // namespace chestnut::engine
