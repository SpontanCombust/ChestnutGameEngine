#ifndef __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__

#include "../system.hpp"

namespace chestnut::engine
{
    class CInputEventDispatchSystem : public ISystem
    {
    public:
        CInputEventDispatchSystem( CEngine& engine );

        void update( float deltaTime ) override;   
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__