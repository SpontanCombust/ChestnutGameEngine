#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/render_layer_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiRenderLayerComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CRenderLayerComponent> m_handle;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

    template<>
    class CComponentToGuiViewMapping<CRenderLayerComponent>
    {
    public:
        using Mapping = CGuiRenderLayerComponentView;
    };

} // namespace chestnut::engine::debug
