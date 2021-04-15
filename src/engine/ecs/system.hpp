#ifndef __CHESTNUT_SYSTEM_H__
#define __CHESTNUT_SYSTEM_H__

#include <cstdint>

namespace chestnut
{
    class ISystem
    {
    public:
        virtual void update( uint32_t deltaTime ) = 0;
        virtual ~ISystem() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_SYSTEM_H__