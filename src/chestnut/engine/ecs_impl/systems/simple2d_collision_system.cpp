#include "simple2d_collision_system.hpp"

#include "../../main/engine.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/collision2d_component.hpp"
#include "../events/collision_event.hpp"

namespace chestnut::engine
{    
    CSimple2DCollisionSystem::CSimple2DCollisionSystem( CEngine& engine ) : ISystem( engine )
    {
        m_collisionQuery = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CCollision2DComponent >()
        );
    }

    CSimple2DCollisionSystem::~CSimple2DCollisionSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_collisionQuery );
    }

    inline bool canCollidersTrigger( ECollisionPolicyFlags policy1, ECollisionPolicyFlags policy2 )
    {
        return ( policy1 & ECollisionPolicyFlags::TRIGGER ) > 0 && ( policy2 & ECollisionPolicyFlags::TRIGGER ) > 0;
    }

    void CSimple2DCollisionSystem::update( float dt )
    {
        getEngine().getEntityWorld().queryEntities( m_collisionQuery );

        m_collisionQuery->forEach(std::function(
            [](CTransform2DComponent& transform, CCollision2DComponent& collision)
            {
                if(collision.collider)
                {
                    collision.collider->setPosition(transform.position);
                    collision.collider->setScale(transform.scale);
                }
            }
        ));


        auto it1 = m_collisionQuery->begin< CTransform2DComponent, CCollision2DComponent >();
        auto end = m_collisionQuery->end< CTransform2DComponent, CCollision2DComponent >();

        // do a check for each pair of the entities
        for(; it1 != end - 1; it1++)
        {
            for(auto it2 = it1 + 1; it2 != end; it2++)
            {
                auto [transform1, collision1] = *it1;
                auto [transform2, collision2] = *it2;
                
                if(!collision1.collider || !collision2.collider)
                {
                    return;
                }
                else if(collision1.collider->getActivity() == EColliderActivity::STATIC && collision2.collider->getActivity() == EColliderActivity::STATIC)
                {
                    return;
                }


                auto crd = collision1.collider->resolveCollision( *collision2.collider );
                if(crd.isCollision)
                {
                    transform1.position += crd.obj1Displacement;
                    transform2.position += crd.obj2Displacement;

                    if(canCollidersTrigger(collision1.collider->getPolicyFlags(), collision2.collider->getPolicyFlags()))
                    {
                        SCollisionEvent e;
                        e.entity1 = it1.entityId();
                        e.entity2 = it2.entityId();
                        e.resolutionData = crd;
                        getEngine().getEventManager().raiseEvent(e);
                    }
                }
            }
        }
    }

    
} // namespace chestnut::engine
