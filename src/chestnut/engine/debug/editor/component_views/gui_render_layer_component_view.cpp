#include "chestnut/engine/debug/editor/component_views/gui_render_layer_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    void CGuiRenderLayerComponentView::fetchComponent(ecs::entityid_t entity)
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CRenderLayerComponent>(entity);
    }

    void CGuiRenderLayerComponentView::drawWidgets()
    {
        ImGui::Text("Layer number");
        ImGui::DragScalar("##LayerNumber", ImGuiDataType_S8, &m_handle->layer);
    }

} // namespace chestnut::engine::debug
