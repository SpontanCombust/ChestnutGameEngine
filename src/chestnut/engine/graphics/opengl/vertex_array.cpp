#include "vertex_array.hpp"

#include "vertex_buffer.hpp"

#include <algorithm>


namespace chestnut::engine
{
    CVertexArray::CVertexArray()
    {
        glGenVertexArrays(1, &m_id);
        m_shouldUpdate = false;
    }

    CVertexArray::~CVertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    CVertexArray::CVertexArray(const CVertexArray& other)
    {
        m_shouldUpdate = true;
        m_vecBuffers = other.m_vecBuffers;
    }

    CVertexArray& CVertexArray::operator=(const CVertexArray& other)
    {
        m_shouldUpdate = true;
        m_vecBuffers = other.m_vecBuffers;

        return *this;
    }

    CVertexArray::CVertexArray(CVertexArray&& other)
    {
        m_id = other.m_id;
        m_shouldUpdate = other.m_shouldUpdate;
        m_vecBuffers = std::move(other.m_vecBuffers);

        other.m_id = 0;
    }

    CVertexArray& CVertexArray::operator=(CVertexArray&& other)
    {
        m_id = other.m_id;
        m_shouldUpdate = other.m_shouldUpdate;
        m_vecBuffers = std::move(other.m_vecBuffers);

        other.m_id = 0;

        return *this;
    }




    void CVertexArray::bind()
    {
        glBindVertexArray(m_id);
    }

    void CVertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void CVertexArray::addBuffer(std::shared_ptr<IBuffer> buffer)
    {
        m_vecBuffers.push_back(buffer);
        m_shouldUpdate = true;
    }

    void CVertexArray::update()
    {
        bind();
        for(auto& buffer : m_vecBuffers)
        {
            buffer->bind();

            if(auto vertexBuffer = std::dynamic_pointer_cast<CVertexBuffer>(buffer))
            {
                vertexBuffer->rebindAttributes();
            }
        }
        unbind();

        m_shouldUpdate = false;
    }

    bool CVertexArray::shouldUpdate() const
    {
        m_shouldUpdate |= std::any_of(m_vecBuffers.begin(), m_vecBuffers.end(), 
            [](const std::shared_ptr<IBuffer>& buffer) {
                if(auto vertexBuffer = std::dynamic_pointer_cast<CVertexBuffer>(buffer))
                {
                    return vertexBuffer->shouldRebindAttributes();
                }
                
                return false;
            }
        );

        return m_shouldUpdate;
    }
    
} // namespace chestnut::engine
