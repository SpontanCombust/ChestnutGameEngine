#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiIdentityComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CIdentityComponent> m_handle;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

    template<>
    class CComponentToGuiViewMapping<CIdentityComponent>
    {
    public:
        using Mapping = CGuiIdentityComponentView;
    };

} // namespace chestnut::engine::debug
