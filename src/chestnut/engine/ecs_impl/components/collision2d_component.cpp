#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"

namespace chestnut::engine
{    
    CCollider2D& CCollision2DComponent::getBaseCollider() 
    {
        return *std::visit([this](CCollider2D& v){
            return &v;
        }, this->colliderVariant);
    }

    const CCollider2D& CCollision2DComponent::getBaseCollider() const
    {
        return *std::visit([this](const CCollider2D& v){
            return &v;
        }, this->colliderVariant);
    }


} // namespace chestnut::engine
