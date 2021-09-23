#include "kinematics2d_component.hpp"

namespace chestnut
{
    CKinematics2DComponent::CKinematics2DComponent()
    {
        linearVelocity = vec2f(0.f);
        linearAcceleration = vec2f(0.f);
        angularVelocity = 0.f;
        angularAcceleration = 0.f;
    }

} // namespace chestnut
