#pragma once

#include <chestnut/ecs/types.hpp>
#include <imgui.h> // include for all inheriting classes

namespace chestnut::engine::debug
{
    class IGuiComponentView
    {
    public:
        virtual ~IGuiComponentView() = default;

        virtual void fetchComponent(ecs::entityid_t entity) = 0;
        virtual void drawGuiWindow() = 0;
    };

} // namespace chestnut::engine::debug
