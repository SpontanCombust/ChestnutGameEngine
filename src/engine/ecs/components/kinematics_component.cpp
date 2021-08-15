#include "kinematics_component.hpp"

namespace chestnut
{
    CKinematicsComponent::CKinematicsComponent()
    {
        linearVelocity = vec2f(0.f);
        linearAcceleration = vec2f(0.f);
        angularVelocity = 0.f;
        angularAcceleration = 0.f;
    }

} // namespace chestnut
