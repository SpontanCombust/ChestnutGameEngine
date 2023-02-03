#include "chestnut/engine/debug/editor/component_views/gui_model2d_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    void CGuiModel2DComponentView::fetchComponent(ecs::entityid_t entity)
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CModel2DComponent>(entity);
    }

    void CGuiModel2DComponentView::drawWidgets()
    {
        ImGui::Text("Size");
        ImGui::DragFloat2("##Size", &m_handle->size.x);

        ImGui::Text("Origin");
        ImGui::DragFloat2("##Origin", &m_handle->origin.x, 0.01f, 0.0f, 1.0f);
    }

} // namespace chestnut::engine::debug
