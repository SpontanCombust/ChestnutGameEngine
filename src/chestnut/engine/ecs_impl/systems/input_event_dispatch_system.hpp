#ifndef __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__

#include "chestnut/engine/macros.hpp"
#include "../system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CInputEventDispatchSystem : public ISystem
    {
    public:
        CInputEventDispatchSystem( CEngine& engine );

        void update( float deltaTime ) override;   
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_INPUT_EVENT_DISPATCH_SYSTEM_H__