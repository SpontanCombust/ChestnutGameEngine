#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API IRenderingSystem : public ISystem
    {
    public:
        IRenderingSystem() : ISystem() 
        {

        }

        IRenderingSystem(systempriority_t priority) : ISystem(priority)
        {

        }

        virtual ~IRenderingSystem() = default;


        virtual void render() = 0;
    };

} // namespace chestnut::engine

