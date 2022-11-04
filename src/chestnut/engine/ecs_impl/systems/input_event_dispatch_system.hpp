#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CInputEventDispatchSystem : public ISystem
    {
    public:
        CInputEventDispatchSystem( CEngine& engine );

        void update( float deltaTime ) override;   
    };

} // namespace chestnut::engine

