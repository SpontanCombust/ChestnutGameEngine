#ifndef __CHESTNUT_ENGINE_BUFFER_H__
#define __CHESTNUT_ENGINE_BUFFER_H__

#include <GL/glew.h>


namespace chestnut::engine
{
    class IBuffer
    {
    public:
        enum EUsage
        {
            STATIC_DRAW     = GL_STATIC_DRAW,
            DYNAMIC_DRAW    = GL_DYNAMIC_DRAW
        };
        
    protected:
        GLuint m_id;
        EUsage m_usage;
        size_t m_currentSize;
           
    public:
        IBuffer();
        IBuffer(EUsage usage);
        ~IBuffer();

        IBuffer(const IBuffer& other);
        IBuffer& operator=(const IBuffer& other);

        // move consturctor and assign declarations
        IBuffer(IBuffer&& other);
        IBuffer& operator=(IBuffer&& other);


        void bind();
        void unbind();


        virtual void allocate(size_t size);

        // If size exceeds current size, the buffer will be resized, but its current data will be lost
        // For better control use allocate() beforehand
        void update(const void* data, size_t size, size_t offset = 0);


    protected:
        virtual GLenum getTypeEnum() const = 0;
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_BUFFER_H__