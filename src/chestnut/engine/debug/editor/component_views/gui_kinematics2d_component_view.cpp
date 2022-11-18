#include "chestnut/engine/debug/editor/component_views/gui_kinematics2d_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{    
    void CGuiKinematics2DComponentView::fetchComponent(ecs::entityid_t entity) 
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CKinematics2DComponent>(entity);
    }

    void CGuiKinematics2DComponentView::drawWidgets() 
    {
        ImGui::Text("Linear velocity");
        ImGui::DragFloat2("##LinearVelocity", &m_handle->linearVelocity.x);

        ImGui::Text("Linear acceleration");
        ImGui::DragFloat2("##LinearAcceleration", &m_handle->linearAcceleration.x);

        ImGui::Text("Angular velocity");
        ImGui::DragFloat("##AngularVelocity", &m_handle->angularVelocity);

        ImGui::Text("Angular acceleration");
        ImGui::DragFloat2("##AngularAcceleration", &m_handle->angularAcceleration);
    }

} // namespace chestnut::engine::debug
