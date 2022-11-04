#include "chestnut/engine/physics/collider2d.hpp"

#include "chestnut/engine/physics/collider2d_collision_detection.hpp"

namespace chestnut::engine
{    
    CCollider2D::CCollider2D()
    {
        m_activity = EColliderActivity::STATIC;
        m_policyFlags = ECollisionPolicyFlags::NONE;
        m_position = vec2f(0.0f, 0.0f);
        m_scale = vec2f(1.0f, 1.0f);
    }

    EColliderActivity CCollider2D::getActivity() const
    {
        return m_activity;
    }

    void CCollider2D::setActivity(EColliderActivity activity)
    {
        m_activity = activity;
    }

    ECollisionPolicyFlags CCollider2D::getPolicyFlags() const
    {
        return m_policyFlags;
    }

    void CCollider2D::setPolicyFlags(ECollisionPolicyFlags policyFlags)
    {
        m_policyFlags = policyFlags;
    }

    vec2f CCollider2D::getPosition() const
    {
        return m_position;
    }

    void CCollider2D::setPosition(vec2f position)
    {
        m_position = position;
    }

    vec2f CCollider2D::getScale() const
    {
        return m_scale;
    }

    void CCollider2D::setScale(vec2f scale)
    {
        m_scale = scale;
    }

    SCollisionResolutionData CCollider2D::isColliding(const CCollider2D& other) const
    {
        return {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};
    }

    SCollisionResolutionData CCollider2D::resolveCollision(CCollider2D& other)
    {
        auto resolutionData = this->isColliding(other);
        if (resolutionData.isCollision)
        {
            this->setPosition(this->getPosition() + resolutionData.obj1Displacement);
            other.setPosition(other.getPosition() + resolutionData.obj2Displacement);
        }

        return resolutionData;
    }




    SCollisionResolutionData CPointCollider2D::isColliding(const CCollider2D& other) const 
    {
        // to avoid having to deal with exceptions thrown when dynamic-casting references
        const CCollider2D *otherPtr = &other;

        if(auto box = dynamic_cast<const CBoxCollider2D *>(otherPtr))
        {
            return checkPointVsBox(*this, *box);
        }
        else if(auto circle = dynamic_cast<const CCircleCollider2D *>(otherPtr))
        {
            return checkPointVsCircle(*this, *circle);
        }
        else
        {
            return {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};
        }
    }




    CBoxCollider2D::CBoxCollider2D()
    {
        m_size = vec2f(0.0f, 0.0f);
    }

    vec2f CBoxCollider2D::getSize() const
    {
        return m_size;
    }

    void CBoxCollider2D::setSize(vec2f size)
    {
        m_size = size;
    }

    vec2f CBoxCollider2D::getRealSize() const
    {
        return m_size * m_scale;
    }

    SCollisionResolutionData CBoxCollider2D::isColliding(const CCollider2D& other) const 
    {
        const CCollider2D *otherPtr = &other;

        if(auto point = dynamic_cast<const CPointCollider2D *>(otherPtr))
        {
            return checkBoxVsPoint(*this, *point);
        }
        else if(auto box = dynamic_cast<const CBoxCollider2D *>(otherPtr))
        {
            return checkBoxVsBox(*this, *box);
        }
        else if(auto circle = dynamic_cast<const CCircleCollider2D *>(otherPtr))
        {
            return checkBoxVsCircle(*this, *circle);
        }
        else
        {
            return {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};
        }
    }




    CCircleCollider2D::CCircleCollider2D()
    {
        m_radius = 0.0f;
    }

    float CCircleCollider2D::getRadius() const
    {
        return m_radius;
    }

    void CCircleCollider2D::setRadius(float radius)
    {
        m_radius = radius;
    }

    vec2f CCircleCollider2D::getRealRadius() const
    {
        return m_radius * m_scale;
    }

    float CCircleCollider2D::getMaxRealRadius() const
    {
        return m_radius * std::max(m_scale.x, m_scale.y);
    }

    SCollisionResolutionData CCircleCollider2D::isColliding(const CCollider2D& other) const 
    {
        const CCollider2D *otherPtr = &other;

        if(auto point = dynamic_cast<const CPointCollider2D *>(otherPtr))
        {
            return checkCircleVsPoint(*this, *point);
        }
        else if(auto box = dynamic_cast<const CBoxCollider2D *>(otherPtr))
        {
            return checkCircleVsBox(*this, *box);
        }
        else if(auto circle = dynamic_cast<const CCircleCollider2D *>(otherPtr))
        {
            return checkCircleVsCircle(*this, *circle);
        }
        else
        {
            return {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};
        }
    }

} // namespace chestnut::engine
