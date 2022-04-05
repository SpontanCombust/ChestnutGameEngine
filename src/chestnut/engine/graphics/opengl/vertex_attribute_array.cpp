#include "vertex_attribute_array.hpp"

#include <numeric>


namespace chestnut::engine
{
    CVertexAttributeArray::CVertexAttributeArray(std::initializer_list<CVertexAttribute> attribs)
    {
        m_vecAttributes.insert(m_vecAttributes.end(), attribs.begin(), attribs.end());
    }

    void CVertexAttributeArray::add(const CVertexAttribute& attribute)
    {
        m_vecAttributes.push_back(attribute);
    }

    void CVertexAttributeArray::enableFor(const CBuffer& buffer) const
    {
        if(buffer.getLayout() == CBuffer::ELayout::STRUCT_OF_ARRAYS)
        {
            enableForStructOfArrays(buffer);
        }
        else if(buffer.getLayout() == CBuffer::ELayout::ARRAY_OF_STRUCTS)
        {
            enableForArrayOfStructs(buffer);
        }
        else
        {
            enableForSingleArray(buffer);
        }
    }

    void CVertexAttributeArray::enableForSingleArray(const CBuffer& buffer) const
    {
        if(m_vecAttributes.size() >= 1)
        {
            const auto& attribute = m_vecAttributes[0];

            glEnableVertexAttribArray(attribute.getLocation());
            if(attribute.getType() == CVertexAttribute::EType::FLOAT)
            {
                glVertexAttribPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    GL_FALSE,
                    0,
                    0
                );
            }
            else
            {
                glVertexAttribIPointer(
                    attribute.getLocation(),
                    attribute.getLength(),
                    attribute.getType(),
                    0,
                    0
                );
            }
            glVertexAttribDivisor(attribute.getLocation(), attribute.getDivisor());
        }
    }

    void CVertexAttributeArray::enableForStructOfArrays(const CBuffer& buffer) const
    {
        size_t arraySize = buffer.getCurrentSize() / getUnderlyingDataSize();

        size_t attribOffset = 0;
        for(const auto& attribute : m_vecAttributes)
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

    void CVertexAttributeArray::enableForArrayOfStructs(const CBuffer& buffer) const
    {
        const size_t structSize = getUnderlyingDataSize();

        size_t attribOffset = 0;
        for(const auto& attribute : m_vecAttributes)
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

    size_t CVertexAttributeArray::getUnderlyingDataSize() const
    {
        return std::accumulate(m_vecAttributes.begin(), m_vecAttributes.end(), 0, 
            [](size_t sum, const CVertexAttribute& attribute)
            {
                return sum + attribute.getTypeSize() * attribute.getLength();
            }
        );
    }

} // namespace chestnut::engine
