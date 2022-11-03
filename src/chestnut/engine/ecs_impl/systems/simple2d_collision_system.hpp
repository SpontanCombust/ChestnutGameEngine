#ifndef __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__
#define __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__

#include "chestnut/engine/macros.hpp"
#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CSimple2DCollisionSystem : public ISystem
    {
    private:
        ecs::CEntityQuery *m_collisionQuery;

    public:
        CSimple2DCollisionSystem( CEngine& engine );
        ~CSimple2DCollisionSystem();

        void update( float dt ) override;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__