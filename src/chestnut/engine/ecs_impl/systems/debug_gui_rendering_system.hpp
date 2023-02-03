#pragma once


#include "chestnut/engine/ecs_impl/rendering_system.hpp"

#include <chestnut/ecs/types.hpp>
#include <chestnut/ecs/constants.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CDebugGuiRenderingSystem : public IRenderingSystem
    {
    private:
        ecs::entityid_t m_selectedEntity = ecs::ENTITY_ID_INVALID;

    public:
        CDebugGuiRenderingSystem() : IRenderingSystem() {}
        CDebugGuiRenderingSystem(systempriority_t priority) : IRenderingSystem(priority) {}

        void render() override;
    };

} // namespace chestnut::engine

