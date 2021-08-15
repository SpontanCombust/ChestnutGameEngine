#include "component_system.hpp"

namespace chestnut
{
    std::vector< ecs::SEntityQuery * >& IComponentSystem::getEntityQueries()
    {
        return m_vecEntityQueries;
    }

} // namespace chestnut
