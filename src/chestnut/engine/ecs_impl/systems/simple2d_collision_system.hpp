#ifndef __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__
#define __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__

#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CSimple2DCollisionSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_query;

    public:
        CSimple2DCollisionSystem( CEngine& engine );

        void update( float dt ) override;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION_SYSTEM_H__