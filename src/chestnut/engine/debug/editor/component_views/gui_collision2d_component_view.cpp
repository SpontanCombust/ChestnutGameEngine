#include "chestnut/engine/debug/editor/component_views/gui_collision2d_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <type_traits>


namespace chestnut::engine::debug
{
    static const char *activityItems[] = {"Static", "Dynamic"};
    static const char *colliderVariants[] = {"Point", "Box", "Circle"};

    void CGuiCollision2DComponentView::fetchComponent(ecs::entityid_t entity)
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CCollision2DComponent>(entity);

        m_selectedActivity = (int)m_handle->getBaseCollider().getActivity();
        m_selectedPolicyAffected = m_handle->getBaseCollider().getPolicyFlags() & ECollisionPolicy::AFFECTED;
        m_selectedPolicyAffecting = m_handle->getBaseCollider().getPolicyFlags() & ECollisionPolicy::AFFECTING;
        m_selectedPolicyTrigger = m_handle->getBaseCollider().getPolicyFlags() & ECollisionPolicy::TRIGGER;
        m_position = m_handle->getBaseCollider().getPosition();
        m_scale = m_handle->getBaseCollider().getScale();

        if(std::holds_alternative<CPointCollider2D>(m_handle->colliderVariant))
        {
            m_selectedColliderVariant = 0;
        }
        else if(auto box = std::get_if<CBoxCollider2D>(&m_handle->colliderVariant))
        {
            m_selectedColliderVariant = 1;
            m_boxSize = box->getSize();
        }
        else if(auto circle = std::get_if<CCircleCollider2D>(&m_handle->colliderVariant))
        {
            m_selectedColliderVariant = 2;
            m_circleRadius = circle->getRadius();
        }
    }

    void CGuiCollision2DComponentView::drawWidgets()
    {
        ImGui::Text("Activity");
        ImGui::Combo("##Activity", &m_selectedActivity, activityItems, IM_ARRAYSIZE(activityItems));

        ImGui::Text("Collision policy");
        ImGui::Checkbox("Affected", &m_selectedPolicyAffected);
        ImGui::SameLine();
        ImGui::Checkbox("Affecting", &m_selectedPolicyAffecting);
        ImGui::SameLine();
        ImGui::Checkbox("Trigger", &m_selectedPolicyTrigger);

        ImGui::Text("Collider variant");
        ImGui::Combo("##Collider variant", &m_selectedColliderVariant, colliderVariants, IM_ARRAYSIZE(colliderVariants));
        if(m_selectedColliderVariant == 0)
        {
            if (!std::holds_alternative<CPointCollider2D>(m_handle->colliderVariant))
            {
                CCollider2D shallowCopy = m_handle->getBaseCollider();
                CPointCollider2D point;

                // shallow copy all base class attributes from the current collider
                *(CCollider2D *)&point = shallowCopy;
                m_handle->colliderVariant = point;
            }
        }
        else if(m_selectedColliderVariant == 1)
        {
            if (!std::holds_alternative<CBoxCollider2D>(m_handle->colliderVariant))
            {
                CCollider2D shallowCopy = m_handle->getBaseCollider();
                CBoxCollider2D box;

                // shallow copy all base class attributes from the current collider
                *(CCollider2D *)&box = shallowCopy;
                m_handle->colliderVariant = box;
            }

            auto& box = std::get<CBoxCollider2D>(m_handle->colliderVariant);
            ImGui::DragFloat2("Box size", &m_boxSize.x);
            box.setSize(m_boxSize);
        }
        else if(m_selectedColliderVariant == 2)
        {
            if (!std::holds_alternative<CCircleCollider2D>(m_handle->colliderVariant))
            {
                CCollider2D shallowCopy = m_handle->getBaseCollider();
                CCircleCollider2D circle;

                // shallow copy all base class attributes from the current collider
                *(CCollider2D *)&circle = shallowCopy;
                m_handle->colliderVariant = circle;
            }

            auto& circle = std::get<CCircleCollider2D>(m_handle->colliderVariant);
            ImGui::DragFloat("Circle radius", &m_circleRadius);
            circle.setRadius(m_circleRadius);
        }

        m_handle->getBaseCollider().setActivity(m_selectedActivity == 0 ? EColliderActivity::STATIC : EColliderActivity::DYNAMIC);
        m_handle->getBaseCollider().setPolicyFlags(
            (m_selectedPolicyAffected   ? ECollisionPolicy::AFFECTED    :   CFlags<ECollisionPolicy>()) |
            (m_selectedPolicyAffecting  ? ECollisionPolicy::AFFECTING   :   CFlags<ECollisionPolicy>()) |
            (m_selectedPolicyTrigger    ? ECollisionPolicy::TRIGGER     :   CFlags<ECollisionPolicy>())
        );
        m_handle->getBaseCollider().setPosition(m_position);
        m_handle->getBaseCollider().setScale(m_scale); 
    }

} // namespace chestnut::engine::debug
