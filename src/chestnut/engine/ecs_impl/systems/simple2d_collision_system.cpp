#include "simple2d_collision_system.hpp"

#include "../../debug/log.hpp"
#include "../../main/engine.hpp"
#include "../../physics/collision_resolution.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/collision2d_component.hpp"
#include "../events/collision_event.hpp"

#include <algorithm> // max

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

        query->forEachEntityPairWith< CTransform2DComponent, CCollision2DComponent >(
            [this]( ecs::entityid ent1, CTransform2DComponent& transform1, CCollision2DComponent& collision1, ecs::entityid ent2, CTransform2DComponent& transform2, CCollision2DComponent& collision2 )
            {
                bool collisionHappened = false;

                // check if both entities aren't static colliders
                // if they're both static we can ignore their interactions
                if( !( collision1.activity == EColliderActivity::STATIC && collision2.activity == EColliderActivity::STATIC ) )
                {   
                    try
                    {
                        if( collision1.bodyType == EColliderBodyType::AABB )
                        {
                            if( collision2.bodyType == EColliderBodyType::AABB )
                            {
                                collisionHappened = resolveAABB2DVsAABB2D( transform1.position,
                                                                           transform1.scale,
                                                                           std::get<SColliderBodyAABB2D>( collision1.bodyVariant ),
                                                                           collision1.policyFlags,
                                                                           transform2.position,
                                                                           transform2.scale,
                                                                           std::get<SColliderBodyAABB2D>( collision2.bodyVariant ),
                                                                           collision2.policyFlags );
                            }
                            else if( collision2.bodyType == EColliderBodyType::CIRCLE )
                            {
                                collisionHappened = resolveAABB2DVsCircle2D( transform1.position,
                                                                             transform1.scale,
                                                                             std::get<SColliderBodyAABB2D>( collision1.bodyVariant ),
                                                                             collision1.policyFlags,
                                                                             transform2.position,
                                                                             std::max( transform2.scale.x, transform2.scale.y ),
                                                                             std::get<SColliderBodyCircle2D>( collision2.bodyVariant ),
                                                                             collision2.policyFlags );
                            }
                            else
                            {
                                collisionHappened = resolveAABB2DVsPoint2D( transform1.position,
                                                                            transform1.scale,
                                                                            std::get<SColliderBodyAABB2D>( collision1.bodyVariant ),
                                                                            collision1.policyFlags,
                                                                            transform2.position,
                                                                            collision2.policyFlags );
                            }
                        }
                        else if( collision1.bodyType == EColliderBodyType::CIRCLE )
                        {
                            if( collision2.bodyType == EColliderBodyType::AABB )
                            {
                                collisionHappened = resolveCircle2DVsAABB2D( transform1.position,
                                                                             std::max( transform1.scale.x, transform1.scale.y ),
                                                                             std::get<SColliderBodyCircle2D>( collision1.bodyVariant ),
                                                                             collision1.policyFlags,
                                                                             transform2.position,
                                                                             transform2.scale,
                                                                             std::get<SColliderBodyAABB2D>( collision2.bodyVariant ),
                                                                             collision2.policyFlags );
                            }
                            else if( collision2.bodyType == EColliderBodyType::CIRCLE )
                            {
                                collisionHappened = resolveCircle2DVsCircle2D( transform1.position,
                                                                               std::max( transform1.scale.x, transform1.scale.y ),
                                                                               std::get<SColliderBodyCircle2D>( collision1.bodyVariant ),
                                                                               collision1.policyFlags,
                                                                               transform2.position,
                                                                               std::max( transform2.scale.x, transform2.scale.y ),
                                                                               std::get<SColliderBodyCircle2D>( collision2.bodyVariant ),
                                                                               collision2.policyFlags );
                            }
                            else
                            {
                                collisionHappened = resolveCircle2DVsPoint2D( transform1.position,
                                                                              std::max( transform1.scale.x, transform1.scale.y ),
                                                                              std::get<SColliderBodyCircle2D>( collision1.bodyVariant ),
                                                                              collision1.policyFlags,
                                                                              transform2.position,
                                                                              collision2.policyFlags );
                            }
                        }
                        else
                        {
                            if( collision2.bodyType == EColliderBodyType::AABB )
                            {
                                collisionHappened = resolvePoint2DVsAABB2D( transform1.position,
                                                                            collision1.policyFlags,
                                                                            transform2.position,
                                                                            transform2.scale,
                                                                            std::get<SColliderBodyAABB2D>( collision2.bodyVariant ),
                                                                            collision2.policyFlags );
                            }
                            else if( collision2.bodyType == EColliderBodyType::CIRCLE )
                            {
                                collisionHappened = resolvePoint2DVsCircle2D( transform1.position,
                                                                              collision1.policyFlags,
                                                                              transform2.position,
                                                                              std::max( transform2.scale.x, transform2.scale.y ),
                                                                              std::get<SColliderBodyCircle2D>( collision2.bodyVariant ),
                                                                              collision2.policyFlags );
                            }
                            // points don't do collision between each other
                        }
                    }
                    catch(const std::bad_variant_access& e)
                    {
                        LOG_WARNING( "Collider type and stored collider body inside variant in collision component from entity " << ent1 << " or " << ent2 << " are not matching!" );
                    }
                    

                    if( collisionHappened && canCollidersTrigger( collision1.policyFlags, collision2.policyFlags ) )
                    {
                        SCollisionEvent e;
                        e.entity1 = ent1;
                        e.entity2 = ent2;
                        getEngine().getEventManager().raiseEvent(e);
                    }
                }
            }
        );
    }

    
} // namespace chestnut::engine
