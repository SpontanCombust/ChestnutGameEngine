#include "simple2d_collision_system.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"
#include "chestnut/engine/ecs_impl/events/collision_event.hpp"

namespace chestnut::engine
{    
    void CSimple2DCollisionSystem::onAttach() 
    {
        m_collisionQuery = CEngine::getInstance().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CCollision2DComponent >()
        );
    }

    void CSimple2DCollisionSystem::onDetach() 
    {
        CEngine::getInstance().getEntityWorld().destroyQuery( m_collisionQuery );
    }

    inline bool canCollidersTrigger( CFlags<ECollisionPolicy> policy1, CFlags<ECollisionPolicy> policy2 )
    {
        return ( policy1 & ECollisionPolicy::TRIGGER ) && ( policy2 & ECollisionPolicy::TRIGGER );
    }

    void CSimple2DCollisionSystem::update( float dt )
    {
        CEngine::getInstance().getEntityWorld().queryEntities( m_collisionQuery );

        m_collisionQuery->forEach(std::function(
            [](CTransform2DComponent& transform, CCollision2DComponent& collision)
            {
                std::visit([&transform](auto& arg) {
                    arg.setPosition(transform.position);
                    arg.setScale(transform.scale);
                }, collision.colliderVariant);
            }
        ));


        if(m_collisionQuery->getEntityCount() >= 2)
        {
            auto it1 = m_collisionQuery->begin< CTransform2DComponent, CCollision2DComponent >();
            auto end = m_collisionQuery->end< CTransform2DComponent, CCollision2DComponent >();

            // do a check for each pair of the entities
            for(; it1 != end - 1; it1++)
            {
                for(auto it2 = it1 + 1; it2 != end; it2++)
                {
                    auto [transform1, collision1] = *it1;
                    auto [transform2, collision2] = *it2;

                    CCollider2D& baseCollider1 = collision1.getBaseCollider();
                    CCollider2D& baseCollider2 = collision2.getBaseCollider();
                    
                    if(baseCollider1.getActivity() == EColliderActivity::STATIC && baseCollider2.getActivity() == EColliderActivity::STATIC)
                    {
                        return;
                    }


                    auto crd = baseCollider1.resolveCollision(baseCollider2);
                    if(crd.isCollision)
                    {
                        transform1.position += crd.obj1Displacement;
                        transform2.position += crd.obj2Displacement;

                        if(canCollidersTrigger(baseCollider1.getPolicyFlags(), baseCollider2.getPolicyFlags()))
                        {
                            SCollisionEvent e;
                            e.entity1 = it1.entityId();
                            e.entity2 = it2.entityId();
                            e.resolutionData = crd;
                            CEngine::getInstance().getEventManager().raiseEvent(e);
                        }
                    }
                }
            }
        }
    }

    
} // namespace chestnut::engine
