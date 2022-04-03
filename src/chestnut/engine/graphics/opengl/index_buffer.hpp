#ifndef __CHESTNUT_ENGINE_INDEX_BUFFER_H__
#define __CHESTNUT_ENGINE_INDEX_BUFFER_H__

#include "buffer.hpp"


namespace chestnut::engine
{
    class CIndexBuffer : public IBuffer
    {
    public:
        CIndexBuffer() = default;
        CIndexBuffer(EUsage usage);

    private:
        GLenum getTypeEnum() const override;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_INDEX_BUFFER_H__