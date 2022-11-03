#ifndef __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_ARRAY_H__
#define __CHESTNUT_ENGINE_VERTEX_ATTRIBUTE_ARRAY_H__

#include "chestnut/engine/macros.hpp"
#include "vertex_attribute.hpp"
#include "buffer.hpp"

#include <initializer_list>
#include <vector>


namespace chestnut::engine
{
    class CHESTNUT_API CVertexAttributeArray
    {
    private:
        std::vector<CVertexAttribute> m_vecAttributes;

    public:
        CVertexAttributeArray() = default;
        CVertexAttributeArray(std::initializer_list<CVertexAttribute> attribs);
        
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