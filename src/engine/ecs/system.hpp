#ifndef __CHESTNUT_SYSTEM_H__
#define __CHESTNUT_SYSTEM_H__

namespace chestnut
{
    class ISystem
    {
    public:
        virtual void update( float deltaTime ) = 0;
        virtual ~ISystem() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_SYSTEM_H__