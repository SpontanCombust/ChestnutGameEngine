#include "vertex_array.hpp"


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

    CVertexArray::CVertexArray(const CVertexArray& other)
    {
        glGenVertexArrays(1, &m_id);
        m_vecBufferBindings = other.m_vecBufferBindings;
        compose();
    }

    CVertexArray& CVertexArray::operator=(const CVertexArray& other)
    {
        m_vecBufferBindings = other.m_vecBufferBindings;
        compose();

        return *this;
    }

    CVertexArray::CVertexArray(CVertexArray&& other)
    {
        m_id = other.m_id;
        m_vecBufferBindings = std::move(other.m_vecBufferBindings);

        other.m_id = 0;
    }

    CVertexArray& CVertexArray::operator=(CVertexArray&& other)
    {
        m_id = other.m_id;
        m_vecBufferBindings = std::move(other.m_vecBufferBindings);

        other.m_id = 0;

        return *this;
    }



    GLuint CVertexArray::getID() const
    {
        return m_id;
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
        m_vecBufferBindings.push_back({buffer, tl::nullopt});
    }

    void CVertexArray::addBuffer(std::shared_ptr<CBuffer> buffer, const CVertexAttributeArray& attributeArray)
    {
        m_vecBufferBindings.push_back({buffer, attributeArray});
    }

    void CVertexArray::compose()
    {
        bind();
        for(auto& binding : m_vecBufferBindings)
        {
            binding.buffer->bind();

            if(binding.attributeArray.has_value())
            {
                binding.attributeArray.value().enableFor(*binding.buffer);
            }
        }
        unbind();
    }
    
} // namespace chestnut::engine
