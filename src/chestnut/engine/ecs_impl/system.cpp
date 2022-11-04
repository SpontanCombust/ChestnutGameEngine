#include "chestnut/engine/ecs_impl/system.hpp"

namespace chestnut::engine
{
    CEngine& ISystem::getEngine() const
    {
        return m_engine;
    }

    ISystem::ISystem( CEngine& engine ) : m_engine( engine ) 
    {

    }

} // namespace chestnut::engine
