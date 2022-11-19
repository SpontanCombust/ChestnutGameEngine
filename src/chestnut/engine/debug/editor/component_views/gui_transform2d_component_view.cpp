#include "chestnut/engine/debug/editor/component_views/gui_transform2d_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    void CGuiTransform2DComponentView::fetchComponent(ecs::entityid_t entity)
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CTransform2DComponent>(entity);
    }

    void CGuiTransform2DComponentView::drawWidgets()
    {
        ImGui::Text("Position");
        ImGui::DragFloat2("##Position", &m_handle->position.x);

        ImGui::Text("Scale");
        ImGui::DragFloat2("##Scale", &m_handle->scale.x, 0.01f);

        ImGui::Text("Rotation");
        ImGui::DragFloat("##Rotation", &m_handle->rotation, 0.01f);
    }

} // namespace chestnut::engine::debug
