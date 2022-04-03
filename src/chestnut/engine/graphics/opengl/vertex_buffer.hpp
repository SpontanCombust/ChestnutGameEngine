#ifndef __CHESTNUT_ENGINE_VERTEX_BUFFER_H__
#define __CHESTNUT_ENGINE_VERTEX_BUFFER_H__

#include "buffer.hpp"
#include "vertex_attribute.hpp"

#include <vector>


namespace chestnut::engine
{
    class CVertexBuffer : public IBuffer
    {
    public:
        enum ELayout
        {
            STRUCT_OF_ARRAYS,
            ARRAY_OF_STRUCTS
            // for now custom layouts are not supported
        };

    private:
        ELayout m_layout;

        bool m_shouldRebindAttribs;
        std::vector<CVertexAttribute> m_vecVertexAttributes;

    public:
        CVertexBuffer();
        CVertexBuffer(EUsage usage, ELayout layout);
        ~CVertexBuffer() = default;

        CVertexBuffer(const CVertexBuffer& other);
        CVertexBuffer& operator=(const CVertexBuffer& other);

        CVertexBuffer(CVertexBuffer&& other);
        CVertexBuffer& operator=(CVertexBuffer&& other);


        void addAttribute(const CVertexAttribute& attribute);
        // For example when it has not been done yet or when the attributes or their offsets have changed
        bool shouldRebindAttributes() const;
        void rebindAttributes();


        void allocate(size_t size) override;


    private:
        void rebindAttributesSOA();
        void rebindAttributesAOS();
        // For AOS it's the size of the single struct instance
        // For SOA it's the accumulated size of types of underlying arrays
        size_t getUnderlyingDataSize() const;

        GLenum getTypeEnum() const override;
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_VERTEX_BUFFER_H__