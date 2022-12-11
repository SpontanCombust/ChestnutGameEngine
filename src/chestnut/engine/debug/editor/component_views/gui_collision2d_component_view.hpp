#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiCollision2DComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CCollision2DComponent> m_handle;

        int m_selectedActivity;
        bool m_selectedPolicyAffected;
        bool m_selectedPolicyAffecting;
        bool m_selectedPolicyTrigger;
        vec2f m_position;
        vec2f m_scale;
        int m_selectedColliderVariant;
        vec2f m_boxSize;
        float m_circleRadius;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

    template<>
    class CComponentToGuiViewMapping<CCollision2DComponent>
    {
    public:
        using Mapping = CGuiCollision2DComponentView;
    };

} // namespace chestnut::engine::debug
