#include "simple2d_collision_system.hpp"

#include "../../main/engine.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/collision2d_component.hpp"
#include "../events/collision_event.hpp"

namespace chestnut::engine
{    
    CSimple2DCollisionSystem::CSimple2DCollisionSystem( CEngine& engine ) : ISystem( engine )
    {
        m_collisionQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CCollision2DComponent >(),
            ecs::makeEntitySignature()
        );
    }

    CSimple2DCollisionSystem::~CSimple2DCollisionSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_collisionQueryID );
    }

    inline bool canCollidersTrigger( ECollisionPolicyFlags policy1, ECollisionPolicyFlags policy2 )
    {
        return ( policy1 & ECollisionPolicyFlags::TRIGGER ) > 0 && ( policy2 & ECollisionPolicyFlags::TRIGGER ) > 0;
    }

    void CSimple2DCollisionSystem::update( float dt )
    {
        const ecs::CEntityQuery* query = getEngine().getEntityWorld().queryEntities( m_collisionQueryID );

        query->forEachEntityWith<CTransform2DComponent, CCollision2DComponent>(
            [this](CTransform2DComponent& transform, CCollision2DComponent& collision)
            {
                if(collision.collider)
                {
                    collision.collider->setPosition(transform.position);
                    collision.collider->setScale(transform.scale);
                }
            }
        );

        query->forEachEntityPairWith< CTransform2DComponent, CCollision2DComponent >(
            [this]( ecs::entityid_t ent1, CTransform2DComponent& transform1, CCollision2DComponent& collision1, ecs::entityid_t ent2, CTransform2DComponent& transform2, CCollision2DComponent& collision2 )
            {
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
                        e.entity1 = ent1;
                        e.entity2 = ent2;
                        e.resolutionData = crd;
                        getEngine().getEventManager().raiseEvent(e);
                    }
                }
            }
        );
    }

    
} // namespace chestnut::engine
