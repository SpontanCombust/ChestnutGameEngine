#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"

namespace chestnut::engine
{
    // Class that provides a default behaviour for when window's 'X' is clicked
    class CHESTNUT_API CDefaultExitSystem : public ILogicSystem
    {
    public:
        CDefaultExitSystem() = default;
        CDefaultExitSystem(systempriority_t priority) : ILogicSystem(priority) {}

        void onAttach() override;

        void update( float deltaTime ) override {}
    };

} // namespace chestnut::engine

