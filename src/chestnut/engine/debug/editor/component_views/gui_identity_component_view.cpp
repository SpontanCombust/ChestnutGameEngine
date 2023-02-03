#include "chestnut/engine/debug/editor/component_views/gui_identity_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    void CGuiIdentityComponentView::fetchComponent(ecs::entityid_t entity)
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CIdentityComponent>(entity);
    }

    void CGuiIdentityComponentView::drawWidgets()
    {
        ImGui::Text("Name");
        ImGui::InputText("##Name", m_handle->name, IM_ARRAYSIZE(m_handle->name));
    }

} // namespace chestnut::engine::debug
