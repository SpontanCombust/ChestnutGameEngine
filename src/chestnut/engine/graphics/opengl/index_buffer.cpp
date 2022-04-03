#include "index_buffer.hpp"

namespace chestnut::engine
{ 
    CIndexBuffer::CIndexBuffer(EUsage usage)
    : IBuffer(usage)
    {

    }

    GLenum CIndexBuffer::getTypeEnum() const 
    {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
   
} // namespace chestnut::engine
