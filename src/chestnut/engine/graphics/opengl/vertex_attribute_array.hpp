#ifndef __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_ARRAY_H__
#define __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_ARRAY_H__

#include "vertex_attribute.hpp"
#include "buffer.hpp"

#include <vector>


namespace chestnut::engine
{
    class CVertexAttributeArray
    {
    private:
        std::vector<CVertexAttribute> m_vecAttributes;

    public:
        void add(const CVertexAttribute& attribute);

        void enableFor(const CBuffer& buffer) const;

    private:
        void enableForSingleArray(const CBuffer& buffer) const;
        void enableForStructOfArrays(const CBuffer& buffer) const;
        void enableForArrayOfStructs(const CBuffer& buffer) const;
        // What's the size of data represented by the collection of attributes
        size_t getUnderlyingDataSize() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_ARRAY_H__