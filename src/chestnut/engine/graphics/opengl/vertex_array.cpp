#include "vertex_array.hpp"

#include <algorithm>


namespace chestnut::engine
{
    CVertexArray::CVertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    CVertexArray::~CVertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void CVertexArray::bind()
    {
        glBindVertexArray(m_id);
    }

    void CVertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void CVertexArray::addBuffer(std::shared_ptr<CBuffer> buffer)
    {
        m_vecBuffers.push_back(buffer);
    }

    void CVertexArray::update()
    {
        bind();
        for(auto& buffer : m_vecBuffers)
        {
            buffer->bind();
            buffer->rebindAttributes();
        }
        unbind();
    }

    bool CVertexArray::shouldUpdate() const
    {
        return std::any_of(m_vecBuffers.begin(), m_vecBuffers.end(), 
            [](const std::shared_ptr<CBuffer>& buffer) {
                return buffer->shouldRebindAttributes();
            }
        );
    }
    
} // namespace chestnut::engine
