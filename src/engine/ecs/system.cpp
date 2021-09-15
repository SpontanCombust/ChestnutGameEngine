#include "system.hpp"

namespace chestnut
{
    CEngine& ISystem::getEngine() const
    {
        return m_engine;
    }

    ISystem::ISystem( CEngine& engine ) : m_engine( engine ) 
    {

    }

} // namespace chestnut
