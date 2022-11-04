#pragma once


#include "chestnut/engine/macros.hpp"

#include <GL/glew.h>


namespace chestnut::engine
{
    class CHESTNUT_API CBuffer
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
            // Single type of data in the buffer layed out contiguously
            SINGLE_ARRAY,
            // Types of data grouped into contiguous arrays that are placed next to each other
            STRUCT_OF_ARRAYS,
            // Types of data grouped into structs that are contiguously repeated throughout the buffer
            ARRAY_OF_STRUCTS
            // for now custom layouts are not supported
        };
        
    protected:
        GLuint m_id;
        EType m_type;
        EUsage m_usage;
        ELayout m_layout;
        size_t m_currentSize;
           
    public:
        CBuffer();
        CBuffer(EType type, EUsage usage, ELayout layout);
        ~CBuffer();

        CBuffer(const CBuffer& other);
        CBuffer& operator=(const CBuffer& other);

        CBuffer(CBuffer&& other);
        CBuffer& operator=(CBuffer&& other);


        GLuint getID() const;
        EType getType() const;
        EUsage getUsage() const;
        ELayout getLayout() const;
        size_t getCurrentSize() const;

        void bind();
        void unbind();


        void reserve(size_t size);

        // If size exceeds current size, the buffer will be resized, but its current data will be lost
        // For better control use allocate() beforehand
        void update(const void* data, size_t size, size_t offset = 0);
    };
    
} // namespace chestnut::engine

