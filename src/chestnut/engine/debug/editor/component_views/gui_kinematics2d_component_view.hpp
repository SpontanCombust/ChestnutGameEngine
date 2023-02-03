#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiKinematics2DComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CKinematics2DComponent> m_handle;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

    template<>
    class CComponentToGuiViewMapping<CKinematics2DComponent>
    {
    public:
        using Mapping = CGuiKinematics2DComponentView;
    };

} // namespace chestnut::engine::debug
