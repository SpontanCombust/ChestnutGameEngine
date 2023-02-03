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
        virtual void drawWidgets() = 0;
    };

    template<class C>
    class CComponentToGuiViewMapping
    {
    public:
        // Set to desired component view type
        using Mapping = nullptr_t;
    };

} // namespace chestnut::engine::debug
