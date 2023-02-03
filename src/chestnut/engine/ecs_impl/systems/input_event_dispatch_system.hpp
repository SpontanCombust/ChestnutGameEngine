#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CInputEventDispatchSystem : public ILogicSystem
    {
    public:
        CInputEventDispatchSystem() = default;
        CInputEventDispatchSystem(systempriority_t priority);

        void update( float deltaTime ) override;   
    };

} // namespace chestnut::engine

