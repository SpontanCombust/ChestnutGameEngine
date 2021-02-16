#ifndef __CHESTNUT_UPDATABLE_SYSTEM_H__
#define __CHESTNUT_UPDATABLE_SYSTEM_H__

namespace chestnut
{
    class IUpdatableSystem
    {
    public:
        virtual void update( float deltaTime ) = 0;
        virtual ~IUpdatableSystem() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_UPDATABLE_SYSTEM_H__