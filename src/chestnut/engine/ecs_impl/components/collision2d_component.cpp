#include "collision2d_component.hpp"

namespace chestnut::engine
{    
    CCollision2DComponent::CCollision2DComponent() 
    {
        activity = EColliderActivity::STATIC;
        bodyType = EColliderBodyType::POINT;
        bodyVariant = SColliderBodyPoint2D();
        policyFlags = ECollisionPolicyFlags::NONE;
    }

} // namespace chestnut::engine
