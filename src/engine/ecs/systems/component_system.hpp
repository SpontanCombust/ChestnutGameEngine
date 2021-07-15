#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "../system.hpp"
#include "../management/component_batch.hpp"

namespace chestnut
{
    class IComponentSystem : public ISystem
    {
    public:
        // A method that passes a component batch to the system. It's performed on every tick.
        virtual void submitComponents( CComponentBatch *batch ) = 0;
        // A method that is supposed to clear batches that were passed to the system. It's performed at the end of every tick (after update). 
        virtual void clearComponents() = 0;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__