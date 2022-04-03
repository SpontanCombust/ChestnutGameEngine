#ifndef __CHESTNUT_ENGINE_BUFFER_H__
#define __CHESTNUT_ENGINE_BUFFER_H__

#include "vertex_attribute.hpp"

#include <GL/glew.h>

#include <vector>


namespace chestnut::engine
{
    class CBuffer
    {
    public:
        enum EType
        {
            VERTEX  = GL_ARRAY_BUFFER,
            INDEX   = GL_ELEMENT_ARRAY_BUFFER
        };
        enum EUsage
        {
            STATIC_DRAW     = GL_STATIC_DRAW,
            DYNAMIC_DRAW    = GL_DYNAMIC_DRAW
        };
        enum ELayout
        {
            STRUCT_OF_ARRAYS,
            ARRAY_OF_STRUCTS
            // for now custom layouts are not supported
        };


    private:
        GLuint m_id;
        EType m_type;
        EUsage m_usage;
        ELayout m_layout;

        size_t m_currentSize;
        bool m_shouldRebindAttribs;
        std::vector<CVertexAttribute> m_vecVertexAttributes;
        

    public:
        CBuffer();
        CBuffer(EType type, EUsage usage, ELayout layout);
        ~CBuffer();

        CBuffer(const CBuffer& other);
        CBuffer& operator=(const CBuffer& other);

        // move consturctor and assign declarations
        CBuffer(CBuffer&& other);
        CBuffer& operator=(CBuffer&& other);


        void bind();
        void unbind();

        void addAttribute(CVertexAttribute&& attribute);
        // For example when it has not been done yet or when the attributes or their offsets have changed
        bool shouldRebindAttributes() const;
        void rebindAttributes();

        void allocate(size_t size);

        // If size exceeds current size, the buffer will be resized, but its current data will be lost
        // For better control use allocate() beforehand
        void update(const void* data, size_t size, size_t offset = 0);

    private:
        void rebindAttributesSOA();
        void rebindAttributesAOS();
        // For AOS it's the size of the single struct instance
        // For SOA it's the accumulated size of types of underlying arrays
        size_t getUnderlyingDataSize() const;
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_BUFFER_H__