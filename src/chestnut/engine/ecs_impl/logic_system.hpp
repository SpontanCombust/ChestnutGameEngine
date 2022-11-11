#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API ILogicSystem : public ISystem
    {
    public:
        ILogicSystem() : ISystem() 
        {

        }

        ILogicSystem(systempriority_t priority) : ISystem(priority)
        {

        }

        virtual ~ILogicSystem() = default;


        virtual void update( float deltaTime ) = 0;
    };

} // namespace chestnut::engine
