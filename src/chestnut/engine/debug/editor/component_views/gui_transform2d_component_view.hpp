#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiTransform2DComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CTransform2DComponent> m_handle;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawGuiWindow() override;
    };

} // namespace chestnut::engine::debug
