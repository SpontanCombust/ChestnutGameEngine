#ifndef __CHESTNUT_ENGINE_SIMPLE2D_ANIMATION_SYSTEM_H__
#define __CHESTNUT_ENGINE_SIMPLE2D_ANIMATION_SYSTEM_H__

#include "chestnut/engine/macros.hpp"
#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CSimple2DAnimationSystem : public ISystem
    {
    private:
        ecs::CEntityQuery *m_animatedTextureQuery;

    public:
        CSimple2DAnimationSystem( CEngine& engine );

        void update( float dt ) override;
    };

} // namespace chestnut::engine


#endif // __CHESTNUT_ENGINE_SIMPLE2D_ANIMATION_SYSTEM_H__