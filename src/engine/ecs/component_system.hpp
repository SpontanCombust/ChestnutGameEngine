#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "system.hpp"

#include <chestnut/ecs/entity_query.hpp>

#include <vector>

namespace chestnut
{
    class IComponentSystem : public ISystem
    {
    protected:
        std::vector< ecs::SEntityQuery * > m_vecEntityQueries;

    public:
        virtual void initQueries() = 0;

        std::vector< ecs::SEntityQuery * >& getEntityQueries();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__